#include <stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<netinet/in.h>
#include<stdio.h>

int main()
{
    int listfd,connfd,retval;
    socklen_t chilen;
    int opt = 1;
    struct  sockaddr_in cliaddr, servaddr;


    listfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listfd < 0){
        perror("Sock:");
        exit(1);
    } 

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(8000);
    if(setsockopt(server_fd, SOL_SOCKET,SO_REUSEADDR| SO_REUSEPORT,&opt,sizeof(opt))){
        perror("setsocket");
        exit(EXIT_FAILURE);
    }
    retval = bind(listfd, (struct  sockaddr*) &servaddr, sizeof(servaddr));
    if(retval < 0){perror("bind: ");
    exit(2);}
    listen(listfd,5);
    while(1){
        chilen  =sizeof(cliaddr);
        connfd = accept(listfd,(struct sockaddr *)&cliaddr, &chilen);
        printf("Client connected\n");
    }

    return 0;
}