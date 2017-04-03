#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>

#define MSG_LEN 1024
#define PORT    5000

int main (int argc, char *argvp[])
{
    int listening_sockfd = 0, connect_sockfd = 0;
    char message[MSG_LEN] = {'\0'};
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_size = sizeof(client_addr);
    size_t bytes = 0;

    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));

    listening_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listening_sockfd < 0)
    {
        printf("Error opening socket\n");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if(bind(listening_sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("Error binding address and port to socket\n");
        close(listening_sockfd);
        exit(EXIT_FAILURE);
    }
    
    printf("Waiting for client connection...\n");
    if(listen(listening_sockfd, 10) < 0)
    {
        printf("Error listening on socket\n");
        close(listening_sockfd);
        exit(EXIT_FAILURE);
    }
    
    connect_sockfd = accept(listening_sockfd, (struct sockaddr *)&client_addr, &client_size);
    if(connect_sockfd < 0)
    {
        printf("Error on accepting client\n");
        close(listening_sockfd);
        exit(EXIT_FAILURE);
    }

    while(1)
    {
        memset(message, 0, sizeof(message));

        printf("Waiting for client's message...\n");
        bytes = recv(connect_sockfd, message, sizeof(message), 0);
        if(bytes < 0)
        {
            printf("Error reading from socket\n");
            close(connect_sockfd);
            close(listening_sockfd);
            exit(EXIT_FAILURE);
        }
        message[MSG_LEN - 1] = '\0';

        printf("Message from client : %s\n", message);

        if(0 == strncmp(message, "exit", 4))
        {
            printf("Exiting...\n");
            close(connect_sockfd);
            close(listening_sockfd);
            exit(EXIT_SUCCESS);
        }

        bytes = send(connect_sockfd, message, (strlen(message) + 1), 0);
        if(bytes < 0)
        {
            printf("Error sending response to client\n");
            close(connect_sockfd);
            close(listening_sockfd);
            exit(EXIT_FAILURE);
        }
    }

    exit(EXIT_SUCCESS);
}
