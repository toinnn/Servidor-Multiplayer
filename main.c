#define PORT 8080
#define BUFF_SIZE 150
#include <stdio.h>
#include <winsock2.h>
#include <pthread.h>
#include <string.h>

#pragma comment(lib, "Ws2_32.lib")

char *meu_concat(char *a, char*b){

    char *c = malloc(sizeof(a)+sizeof(b));
    int a_len = strlen(a);
    int i ;
    for(i=0; i< a_len ; i++)
    {
        c[i] = 0;
        c[i]+=a[i];
    }

    for( i=0; i< strlen(b); i++)
    {
        c[i + a_len] = b[i];
    }
    printf("O C final e %s" , c);
    return c;
}
char *mystrcat(char *a, char *b) {
  char *p, *q, *rtn;
  rtn = q = malloc(strlen(a) + strlen(b) + 1);
  for (p = a; (*q = *p) != '\0'; ++p, ++q) {}
  for (p = b; (*q = *p) != '\0'; ++p, ++q) {}
  return rtn;
}

void http_request(char *msg , int client_sock ){

    char response[] = "HTTP/1.1 200 OK\n" ;
    char aux[500] = "teste//";
    //response = response + "Content-Type: image/png\n\n" ;
    strcat(response ,"Content-Type: image/png\n\n") ;

    //char a = msg[0];
    printf("response == %s\n" , msg );
    //strcat(response , fopen(msg,"rb") ) ;
    printf("Eu respondo requests http OU NAO\n");
    send(client_sock , response , sizeof(response) , 0 );
    fflush(stdout) ;
}
void connect_players(){
    printf("Eu conecto players ");
    return ;
}
void *handle_request(void *client_sock_tmp ){
    printf("Entrou no handle\n");
    int client_sock = *((int*)client_sock_tmp);
    free(client_sock_tmp);

    char buff[BUFF_SIZE];

    int x = recv(client_sock , buff ,sizeof( buff) , 0);
    printf("Passou no recv\n");
    printf("\na requisicao de entrada e :\n%s\n\n", buff);
    char * token = strtok(buff, " ");
    //Define se é uma conexão Http ou de entrada na partida e chama a devida função
    printf("a requisicao de entrada e :\n%s\n", buff);
    if(!strcmp(buff ,"GET") ){
        char oi[300] = "C:\\Users\\limaa\\OneDrive\\Documentos\\CodeBlocks Projects\\Servidor-Multiplayer-Ap2\\Server" ;
        token = strtok(NULL, " ") ;
        strcat(oi ,token) ;
        char a[] = "HTTP/1.1 200 OK\nContent-Type: image/png\n\n";
        /*strcat(a , ");
        strcat(a , ");*/

        int c = getc;
        FILE *file ;/*, *file2;
        file2 = fopen("C:\\temporario_me_apague.txt","w");
        fprintf(file2 ,"%s", a );
        if (file2) {
            while ((c = getc(file2)) != EOF)
        putchar(c);
        fclose(file2);
        }*/
        file = fopen(oi, "r");
        int index = 0 ;
        char output[2000] = {0x00};
        if (file) {
            while ((c = getc(file)) != EOF)
        //putchar(c);
        output[index++] = (char)putchar(c);
        fclose(file);
}       char d[1000] ;
        sprintf(d , "%d" , c);
        printf("Concatenou\n");

        char *msg = meu_concat(&a,&output);

        printf("minha msg %s" , msg );
        /*strcat(a , (char )c);*/
        //printf("ola %s\n" , c );

        //printf("%s\n" , buff);
        //http_request( token , client_sock );
    }else if (buff == "MSG"){
        connect_players();
    }/*else{
        return bad_request;
    }
    */
    //return ;
}
void start_server( ){
        WSADATA wsa ;
   WSAStartup(MAKEWORD(2, 0 ), &wsa);

     struct sockaddr_in caddr ;
     struct sockaddr_in saddr = {
         .sin_family = AF_INET,
         .sin_addr.s_addr = htonl(INADDR_ANY),
         .sin_port = htons(PORT)
     } ;

    int server = socket(AF_INET, SOCK_STREAM,0) ;
    int client , csize = sizeof caddr , x;

    bind(server , (struct sockaddr* ) &saddr , sizeof(saddr) ) ;
    listen(server ,5 );

    printf("[Server Ouvindo...]");

    while(1)
    {   printf("Chegou no client\n");
        client = accept(server , (struct sockaddr* ) &caddr , &csize );
        printf("Passou do client\n");
        //x = recv(client , buff ,sizeof buff , 0);
        if(client >= 0 ){
                printf("Entrou no if\n");
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

    printf("Foi_Meu_FILHO_FOI_testeOoo!\n");

    start_server();

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
