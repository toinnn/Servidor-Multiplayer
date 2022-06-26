from js import document
import js
from pyodide import to_js, create_proxy

# pipe = document.querySelector(".pipe")
mario = document.querySelector(".mario")
buttom_jump = document.querySelector(".button_jump")
# def if_stop(pos , Pipe):
#     if pos <= 120 and float(mario.style.bottom[:-2]) <= 70 and pos >= 0 :
#         Pipe.style.animation = "none"
#         Pipe.style.left = f"{pos}px"
#         mario.src = "images//game-over.png"
#         mario.style.width = "75px"
#         buttom_jump.textContent = "Re-Start"
def jump(entity):
    var =js.window.getComputedStyle( mario).bottom
    pyscript.write('msg',var[:-2])
    
    mario.style.bottom = f"{float(var[:-2]) + 80}px"
    
    var =js.window.getComputedStyle( mario).bottom
    pyscript.write('msg',var[:-2])

# mario.addEventListener("click" , create_proxy(jump) )

class game():
    def __init__(self) -> None:
        
        # self.pipe = document.querySelector(".pipe")
        self.mario = document.querySelector(".mario")
        self.board = document.querySelector(".game-board")
        self.velocity = 0
        self.g = 50
        self.buttom_Jump = False
        self.obstacles = []
        self.last_obstacle_id = 0
        self.game_stoped = False
        self.score_record = 0
        self.score = 0

        # self.add_elem("images//pipe.png")
        self.add_double_elem("images//Flappy_pipe_long.png")
        # self.mario.style.bottom = "-30px"
        # self.pipe.style.animationPlayState = 'paused'

    def gravity(self , ms = 1000) -> None :
        """ms == milisegundos entre cada step do loop de movimento """
        var =js.window.getComputedStyle( self.mario).bottom
        ms = ms/200

        if self.velocity >=0 :
            self.mario.style.bottom = f"{max(float(var[:-2]) - (self.velocity**2)/(2*self.g)*ms ,0 )}px"
        else :
            self.mario.style.bottom = f"{max(float(var[:-2]) + (self.velocity**2)/(2*self.g)*ms ,0 )}px"
        if float(js.window.getComputedStyle( mario).bottom[:-2]) > 0 :
            self.velocity += self.g*ms
        else :
            self.velocity = 0

    def jump(self , entity):
        var =js.window.getComputedStyle( mario).bottom
        pyscript.write('msg',var[:-2])
        
        # mario.style.bottom = f"{float(var[:-2]) + 80}px"
        # js.console.log(f"entrou e self.buttom_Jump = {self.buttom_Jump}")
        if self.buttom_Jump :
            #PULA
            var =js.window.getComputedStyle( mario).bottom
            pyscript.write('msg',var[:-2])
            self.velocity = -110
        else   : 
            #INICIA UMA PARTIDA
            self.velocity = -110
            buttom_jump.textContent = "Jump"
            self.buttom_Jump = True
            mario.src = "images//mario.gif"
            mario.style.width = "150px"
            # pipe.style.left = "800px"
            # pipe.style.animation = 'pipe_move 2.5s infinite linear'
            # pipe.style.animationPlayState = 'running'
            for i in self.obstacles :
                # aux = i
                self.obstacles.remove(i)
                self.board.removeChild(i[0])
                self.board.removeChild(i[1])
                # i.style.animationPlayState = 'running'
            # self.add_elem("images//pipe.png")
            self.add_double_elem("images//Flappy_pipe_long.png")
            self.game_stoped = False
            self.score = 0

    def game_loop_iteration(self):
        if self.game_stoped != True and self.buttom_Jump : #Game Not Stoped
            for i in range(len(self.obstacles)) :
                if self.obstacles[i][2] :
                    self.if_stop(self.obstacles[i] )
                    if self.if_hit( self.obstacles[i] ) :
                        # self.obstacles[i][2] = False
                        self.obstacles[i] = (self.obstacles[i][0] , self.obstacles[i][1] , False)

                self.if_out( self.obstacles[i] ,-490)#24)
                
            # if self.game_stoped == True :
            #     for i in self.obstacles :
            #         i[0].style.animationPlayState = 'paused'
            #         i[1].style.animationPlayState = 'paused'
    
    def if_hit(self , Pipe):
        if Pipe[0].offsetLeft <= -420 :
            self.score += 1
            return True
        return False
    def if_out(self , pipe_pair , screen_offset):
        if pipe_pair[0].offsetLeft <= screen_offset :
            self.obstacles.remove( (pipe_pair[0] , pipe_pair[1] , False ) )
            self.board.removeChild(pipe_pair[0])
            self.board.removeChild(pipe_pair[1])
            js.console.log("Objeto removido")
            self.add_double_elem("images//Flappy_pipe_long.png")

    def if_stop(self, Pipe_pair):
        #Offset entre cabeça do Mario e Cano é de 580px :160px
        #Offset entre pé do Mario e Cano é de 85px : 505px
        pos_under = Pipe_pair[0].offsetLeft
        # pos_above = Pipe_pair[1].offsetLeft
        
        pipe_under_higher = float(Pipe_pair[0].style.bottom[:-2])
        pipe_above_higher = float(Pipe_pair[1].style.bottom[:-2])
        mario_higher = float(mario.style.bottom[:-2])
        
        if pos_under <= -260 and pos_under >= -490 and self.buttom_Jump == True:
            if  mario_higher >= (pipe_above_higher + 160) or mario_higher <= (pipe_under_higher + 505):
                # Pipe.style.animation = "none"
                for i in self.obstacles :
                    i[0].style.animationPlayState = 'paused'
                    i[1].style.animationPlayState = 'paused'
                # Pipe.style.left = f"{pos}px"
                mario.src = "images//game-over.png"
                mario.style.width = "75px"
                buttom_jump.textContent = "Re-Start"
                self.buttom_Jump = False
                self.game_stoped = True
                msg = f"SCORE FOI DE : {self.score}\n++ ÚLTIMO RECORD É DE {self.score_record} "
                # js.console.log()
                if self.score > self.score_record :
                    self.score_record = self.score
                    msg += f"++ \nNOVO RECORDE É DE : {self.score_record}"
                js.console.log(msg)
                pyscript.write('msg',msg)
    def add_double_elem(self,src):
        first = self.add_elem(src)
        secon = self.add_elem(src)
        pipe_non_counted = True
        self.obstacles += [(first , secon , pipe_non_counted )]
        self.obstacles[-1][0].style.bottom = "-450px"
        self.obstacles[-1][0].style.width = ""

        self.obstacles[-1][1].style.bottom = "-30px"
        self.obstacles[-1][1].style.width = ""
        self.obstacles[-1][1].style.transform = "rotate(180deg) scaleX(-1)"
    def add_elem(self, src):
        new_image = document.createElement('img')
        new_image.src = src
        new_image.classList.add(f"obstacle_{self.last_obstacle_id}")
        new_image.style.width = "80px"
        new_image.style.position = "absolute"
        self.board.appendChild(new_image)
        new_image.style.right = "-24px"
        new_image.style.bottom = "0"
        
        self.last_obstacle_id += 1
        new_image.style.animation = "pipe_long_move 2.0s infinite linear"
        # new_image.style.left = "-420px"
        return new_image
        # self.obstacles += [new_image]
        print("Ele criou o novo objetoooooo!!!!!!ooooo")
        
    """def pipe_move(self , pipe_speed , Pipe ):
        # var = js.window.getComputedStyle( Pipe).left
        js.console.log("entrou")
        js.console.log( f"Era pra ter movido : {Pipe.offsetLeft}")
        Pipe.style.right = f"{int(Pipe.style.right[:-2]) + pipe_speed }px"
        if Pipe.offsetLeft < -24 :
            # self.board.removeChild(Pipe)
            Pipe.style.right = "-24px"  """

def main():
    # pyscript.write('msg', 'Hello world')

    # mario_pos = mario.getBoundingClientRect()
    # pipe_pos = pipe.getBoundingClientRect()
    jogo = game()
    
    js.setInterval(to_js(lambda : jogo.game_loop_iteration() ) , 10 )
    jump(mario)
    jump(mario)
    buttom_jump.textContent = "Start"
    # js.setInterval(to_js(lambda : js.console.log( f"{mario.offsetLeft }")) , 50 )
    # js.setInterval(to_js(lambda : pyscript.write("msg" ,pipe.offsetLeft )) , 50 )

    mario.addEventListener("click" , create_proxy(jogo.jump) )
    buttom_jump.addEventListener("click" , create_proxy(jogo.jump) )
    js.setInterval(to_js(lambda : jogo.gravity(50 )) , 50 )
    
    # pipe.style.left = "250px"
    
    # js.setInterval(to_js(lambda : pyscript.write("msg" ,pipe_pos.left)) , 50 )
    
    
main()


# while True:
#     main()
#     time.sleep(2)