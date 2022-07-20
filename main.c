#define PORT 8080
#define BUFF_SIZE 150
#include <stdio.h>
#include <winsock2.h>
#include <pthread.h>
#include <string.h>
///#include <netinet.h>


#pragma comment(lib, "Ws2_32.lib")

char* iso88959_to_utf8(const char *str)
{
    char *utf8 = malloc(1 + (2 * strlen(str)));

    if (utf8) {
        char *c = utf8;
        for (; *str; ++str) {
            if (*str & 0x80) {
                *c++ = *str;
            } else {
                *c++ = (char) (0xc0 | (unsigned) *str >> 6);
                *c++ = (char) (0x80 | (*str & 0x3f));
            }
        }
        *c++ = '\0';
    }
    free(str);
    return utf8;
}

short end_with(char* str1, char* str2){
    char *pointer = strstr(str1 , str2) ;
    //char result[100];
    //memcpy(result , str1 + pointer, strlen(str1) - (pointer - str1));
    return pointer != NULL ;
}
int get_file_size(char *filename) // path to file
{
    FILE *p_file = NULL;
    p_file = fopen(filename,"rb");
    fseek(p_file,0,SEEK_END);
    int size = ftell(p_file);
    fclose(p_file);
    return size;
}
char* concat_str(char* str1, char* str2) {
    int new_len = strlen(str1) + strlen(str2) ;
    char* result = malloc(new_len );
    memset(result , 0 , new_len);
    memcpy(result, str1, strlen(str1));
    memcpy(result + strlen(str1), str2, strlen(str2));
    return result;
}
char *meu_concat(char *a, char*b){

    char *c = malloc(strlen(a)+strlen(b));
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
    //printf("O C final e %s" , c);
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
        char a[61];
        if( end_with(token , ".css") ){
            printf("TERMINOU COM .CSS MEU PARCEIRO !!!!!!!!!!");
            char a[] = "HTTP/1.1 200 OK\r\nContent-Type: text/css \r\n";
        }else if( end_with(token , ".png") || end_with(token , ".jpg") ){
            printf("TERMINOU COM .PNG MEU PARCEIRO !!!!!!!!!!");
            char a[] = "HTTP/1.1 200 OK\r\nContent-Type: image/png \r\n";
        }else if(end_with(token , ".gif")){
            printf("TERMINOU COM .GIF MEU PARCEIRO !!!!!!!!!!");
            char a[] = "HTTP/1.1 200 OK\r\nContent-Type: image/gif \r\n";
        }else {
            printf("TERMINOU COM .HTML MEU PARCEIRO !!!!!!!!!!");
            char a[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html \r\n";}


        int f_len = get_file_size(oi);
        int c = getc;
        FILE *file ;
        file = fopen(oi, "rb");

        int index = 0 ;
        char output[f_len ]; //= {0x00};
        memset(output, 0 , f_len);
        if (file) {
            int i = 0 ;
            ///while( (fgets(&output[i++],sizeof(char)+1,file) != NULL) && (i<f_len) ) ;
            fread(&output , 1, f_len  , file );
        fclose(file);
}
        printf("Concatenou\n");

        ///char *msg = meu_concat(&a,&output);
        /*write(client_sock , &a ,strlen(a));
        write(client_sock , &output ,f_len);*/
        char *msg = concat_str(&a,&output);
        printf("minha msg :\n\n%s" , msg );



        ///send(client_sock , a , strlen(a) , 0 );
        ///send(client_sock , &output , strlen(output) , 0 );
        send(client_sock , msg , strlen(msg) , 0 );
        fflush(stdout) ;
        free(msg);


        //free(sai);
        //closesocket(client_sock);
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
