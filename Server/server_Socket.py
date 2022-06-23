from socket import *
import threading


# addr = ()

class server_skt():
    def __init__(self , server_Name = gethostbyname(gethostname()) , server_Port = 80) -> None:
        # server_Name = '/path/to/my/socket'
        self.skt_Server  = socket(AF_INET , SOCK_STREAM)
        self.skt_Server.bind((server_Name , server_Port))
        self.skt_Server.listen(3)
        
        print("Server Ligado ", server_Name )
    
    def handle_request(self , connection , addr):
        print("[NOVA Conexão..]")

        while True :
            msg = connection.recv(1024).decode('utf-8')
            if msg :
                print(msg)
                cmd_request = msg.split(' ')
                method = cmd_request[0]
                args = [cmd_request[1]]
                print('Client request ',args)
                for i in args:
                    response = ""
                    header   = ""
                    i = i.lstrip('/')
                    try :
                        file = open(i,"rb")
                        print("Abriu o ark")
                        response = file.read()
                        file.close()
                        
                        header = 'HTTP/1.1 200 OK\n'
                        if i.endswith(".png"):
                            header += f"Content-Type: image/png"+"\n\n"
                        elif i.endswith(".gif") :
                            header += f"Content-Type: image/gif"+"\n\n"
                        elif i.endswith(".css") :
                            header += f"Content-Type: text/css"+"\n\n"
                        else:
                            header += f"Content-Type: text/html"+"\n\n"
                        header = header.encode('utf-8')
                        print("Achou")
                    except Exception as e:
                        print("Não achou")
                        header   = 'HTTP/1.1 404 Not Found\n\n'.encode('utf-8')
                        response = '<html><body><center><h3>Error 404: File not found</h3><p>Python HTTP Server</p></center></body></html>'.encode('utf-8')

                    final_response  = header
                    final_response += response#.decode('utf-8')
                    connection.send(final_response)#.encode('utf-8'))
                connection.close()
                return

    def start_server(self):
        # listen()
        print("[Server Ouvindo...]")
        while True:
            
            client , addr = self.skt_Server.accept()
            
            td = threading.Thread(target = self.handle_request , args=(client, addr))
            td.start()

server = server_skt(server_Name = "0.0.0.0")
server.start_server()
