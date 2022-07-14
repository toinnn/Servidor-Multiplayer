#define PORT 8080

#include <stdio.h>
#include <winsock2.h>
#include "include/pthread.h"

#pragma comment(lib, "Ws2_32.lib")
struct 
void request_handle(){

    return ;
}
void start_server(int client , int x , char buff , int csize , int caddr , int server ){
    printf("[Server Ouvindo...]");

    while(1)
    {
        client = accept(server , (struct sockaddr* ) &caddr , &csize );
        x = recv(client , buff ,sizeof buff , 0);
        if(x > 0){
            //Chama nova thread()
            pthread_t tdid;
            pthread_create(&tdid , NULL , request_handle , (void*)td);
        }
    }
    /*while True:
            
            client , addr = self.skt_Server.accept()
            
            td = threading.Thread(target = self.handle_request , args=(client, addr))
            td.start()*/

}
int main(){
    char buff[129];
    WSADATA wsa ;
   WSAStartup(MAKEWORD(2, 0 ), &wsa);

     struct sockaddr_in caddr ;
     struct sockaddr_in saddr = {
         .sin_family = AF_INET,
         .sin_addr.s_addr = htonl(INADDR_ANY),
         .sin_port = htons(5000)
     } ;

    int server = socket(AF_INET, SOCK_STREAM,0) ;
    int client , csize = sizeof caddr , x;

    bind(server , (struct sockaddr* ) &saddr , sizeof saddr) ;
    listen(server ,5 );

    printf("Foi_Meu_FILHO_FOI_testeOoo!");

    /*
    while(1){
        printf("Ola eu sou um teste");
        client = accept(server , (struct sockaddr* ) &caddr , &csize );
        x = recv(client , buff ,sizeof buff , 0);

        send(client, buff , x , 0);
        puts(buff);
        fflush(stdout);

        closesocket(client);

    }*/
    
    // int server_fd, new_socket, valread;
    // struct sockaddr_in address;
    // int opt = 1;
    // int addrlen = sizeof(address);
    // char buffer[1024] = { 0 };
    // char* hello = "Hello from server";

    // // Creating socket file descriptor
    // if ((server_fd = socket(AF_INET, SOCK_STREAM, 0))
    //     == 0) {
    //     perror("socket failed");
    //     exit(EXIT_FAILURE);
    // }
  
    // // Forcefully attaching socket to the port 8080
    // if (setsockopt(server_fd, SOL_SOCKET,
    //                SO_REUSEADDR | SO_REUSEPORT, &opt,
    //                sizeof(opt))) {
    //     perror("setsockopt");
    //     exit(EXIT_FAILURE);
    // }
    // address.sin_family = AF_INET;
    // address.sin_addr.s_addr = INADDR_ANY;
    // address.sin_port = htons(PORT);

    pthread_exit(NULL) ;
    return 0;
}
