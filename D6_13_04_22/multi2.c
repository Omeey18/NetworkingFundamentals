#include <stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/time.h>
#include<fcntl.h>

int main()
{
    int fd1, fd2;
    char buf[10];
    fd_set read_set, write_set, except_set;
    struct timeval timeout;

    int n;
    timeout.tv_sec = 90;
    fd1 = open("./hello", O_RDWR);
    fd2 = open("./hello2",O_RDWR);

    FD_ZERO(&read_set);
    // FD_ZERO(&write_set);
    // FD_ZERO(&except_set);


    FD_SET(fd1,&read_set);
    FD_SET(fd2,&read_set);
     
    n = select(FD_SETSIZE,&read_set,NULL,NULL,&timeout);
if(n<0){
    perror("select");
    exit(1);
}
    // FD_ISSET();  checking particular fd is set or not
    if(FD_ISSET(fd1,&read_set)){
        printf(" REading from fd1 (hello)\n");
        n= read(fd1,buf,10);
        printf(" Read %d from hello \n",n);
    } 
    if(FD_ISSET(fd2,&read_set)){
        printf(" REading from fd2 (hello2)\n");
        n= read(fd2,buf,10);
        printf(" Read %d from hello2 \n",n);
    } 
printf(" no of descriptor ready = %d\n",n);

    return 0;
}