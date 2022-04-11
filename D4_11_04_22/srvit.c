#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>

#define PORT 8000
#define MAXSZ 100

int main()
{
    int sockfd;    // to create socket
    int newsockfd; // to accept connection

    struct sockaddr_in serverAddress; // server receive on this address
    struct sockaddr_in clientAddress; // server sends to client on this address

    int n;
    char msg[MAXSZ];
    int clientAddressLength;

    // create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // initialize the socket address

    memset(&serverAddress, 0, sizeof(serverAddress));

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(PORT);

    // bind the socket with the server address and port

    bind(sockfd, (struct sockaddr *)&serverAddress, sizeof(serverAddress));

    // listen for connection from client
    listen(sockfd, 5);

    // accept a connection

    while (1)
    {
        printf("\n****server waiting for new client conncection***\n");
        clientAddressLength = sizeof(clientAddress);
        newsockfd = accept(sockfd, (struct sockaddr *)&clientAddress, &clientAddress);

        // receive from client

        while (1)
        {
            n = recv(newsockfd, msg, MAXSZ, 0);
            if (n == 0)
            {
                close(newsockfd);
                break;
            }
            msg[n] = 0;
            send(newsockfd, msg, n, 0);
            printf("Receive and set: %s\n", msg);
        } // close inteirior while
    }     // close exterior while
    return 0;
}