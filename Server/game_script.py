from js import document
import js
from pyodide import to_js, create_proxy

pipe = document.querySelector(".pipe")
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
        
        self.pipe = document.querySelector(".pipe")
        self.mario = document.querySelector(".mario")
        self.board = document.querySelector(".game-board")
        self.velocity = 0
        self.g = 50
        self.buttom_Jump = False
        self.obstacles = []
        self.last_obstacle_id = 0
        self.game_stoped = False

        self.add_elem("images//pipe.png")
        self.pipe.style.animationPlayState = 'paused'

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
        js.console.log(f"entrou e self.buttom_Jump = {self.buttom_Jump}")
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
                i.style.animationPlayState = 'running'
            self.game_stoped = False

    def game_loop_iteration(self):
        if self.game_stoped != True : #Game Not Stoped
            for i in self.obstacles :
                self.if_stop(i )
                self.if_out( i ,-24)
            if self.game_stoped == True :
                for i in self.obstacles :
                    i.style.animationPlayState = 'paused'
        
        self.if_stop(self.pipe)
        # self.if_out( ,-24)
        pass
    def if_out(self , pipe , screen_offset):
        # for i in self.obstacles :
        if pipe.offsetLeft <= screen_offset :
            # self.obstacles.remove(pipe)
            # self.board.removeChild(pipe)
            js.console.log("Objeto removido")

    def if_stop(self, Pipe):
        pos = Pipe.offsetLeft
        if pos <= 120 and float(mario.style.bottom[:-2]) <= 70 and pos >= 0 and self.buttom_Jump == True:
            # Pipe.style.animation = "none"
            Pipe.style.animationPlayState = 'paused'
            # Pipe.style.left = f"{pos}px"
            mario.src = "images//game-over.png"
            mario.style.width = "75px"
            buttom_jump.textContent = "Re-Start"
            self.buttom_Jump = False
            self.game_stoped = True

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
        new_image.style.animation = "pipe_move 2.0s infinite linear"
        self.obstacles += [new_image]
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

    mario_pos = mario.getBoundingClientRect()
    pipe_pos = pipe.getBoundingClientRect()
    jogo = game()
    
    js.setInterval(to_js(lambda : jogo.game_loop_iteration() ) , 1 )
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