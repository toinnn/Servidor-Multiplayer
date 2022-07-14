#define PORT 8080
#define BUFF_SIZE 150
#include <stdio.h>
#include <winsock2.h>
#include <pthread.h>
#include <string.h>

#pragma comment(lib, "Ws2_32.lib")

void http_request(char *msg ){
    printf("Eu respondo requests http");
    return ;
}
void connect_players(){
    printf("Eu conecto players ");
    return ;
}
void *handle_request(void *client_sock_tmp ){
    int client_sock = *((int*)client_sock_tmp);
    free(client_sock_tmp);

    char buff[BUFF_SIZE];
    int x = recv(client_sock , buff ,sizeof( buff) , 0);

    //Define se é uma conexão Http ou de entrada na partida e chama a devida função
    /*
    if(http){
        http_request();
    }else if (to_connect_player){
        connect_players();
    }else{
        return bad_request;
    }
    */
    //return ;
}
void start_server(int client , int x , char buff , int csize , int caddr , int server ){
    printf("[Server Ouvindo...]");

    while(1)
    {
        client = accept(server , (struct sockaddr* ) &caddr , &csize );
        //x = recv(client , buff ,sizeof buff , 0);
        if(client >= 0 ){
            //Chama nova thread()
            pthread_t tdid;
            int *client_sock = malloc(sizeof(int));
            *client_sock = client ;
            pthread_create(&tdid , NULL , handle_request , client_sock );
        }//Renomiei o pthreadVC2 para o .lib
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
