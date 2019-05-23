#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>


#define BUFF_SIZE 1024


int main(){

    int server_socket, client_socket, client_len;
    struct sockaddr_in server_addr, client_addr;
    char buff_read[BUFF_SIZE];
    //FILE *file;

    printf("server\n");
    server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if( -1 == server_socket){
        printf("Make server_socket failed \n");
        exit(1);
    }
    memset(&server_addr, 0, sizeof(server_addr));
    //printf("3\n");
    server_addr.sin_family = AF_INET;
    //printf("22\n");
    server_addr.sin_port = htons(9900);
    //printf("44\n");
    server_addr.sin_addr.s_addr = inet_addr("192.168.10.100");
    printf("IP : %s \n", inet_ntoa(server_addr.sin_addr));
    if( -1 == bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr))){
        printf("bind error \n");
        exit(1);
    }
    printf("bind\n");
    if(-1 == listen(server_socket, 5)){
        printf("listen failed \n");
        exit(1);
    }
    printf("listen\n");
    client_len = sizeof(client_addr);
    client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
    if(client_socket == -1){
        printf("accept error \n");
        exit(1);
    }
    printf("aceept \n");
    //file = fopen("/root/Desktop/Read.txt","r");
    /*if(file == NULL){
        printf("Can 't find file \n");
        exit(1);
    }*/
    //printf("file open\n");
    while(1){
        /*if(feof(file) != 0){
            printf("file done\n");
            break;
        }*/
        if(-1 == recv(client_socket, buff_read, BUFF_SIZE, 0)){
            printf("read error \n");
            exit(1);
        }
        printf("%s", buff_read);
    }

    //fclose(file);
    printf("END\n");
    close(server_socket);

}

