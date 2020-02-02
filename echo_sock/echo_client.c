#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

#define HOST    "localhost"
#define MSG_LEN 1024
#define PORT    5000

int main(int argc, char *argvp[])
{
    int sockfd = 0;
    char message[MSG_LEN] = {'\0'};
    struct sockaddr_in server_addr;
    struct hostent *server = NULL;
    size_t bytes = 0;

    memset(&server_addr, 0, sizeof(server_addr));

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        printf("Error opening socket\n");
        exit(EXIT_FAILURE);
    }

    server = gethostbyname(HOST);
    if (NULL == server) {
        printf("gethostbyname() failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    memcpy(server->h_addr, &(server_addr.sin_addr.s_addr), server->h_length);
    server_addr.sin_port = htons(PORT);

    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr))
            < 0) {
        printf("Connecting to server failed\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        memset(message, 0, sizeof(message));

        printf("Enter message: ");
        fgets(message, (sizeof(message)), stdin);
        message[MSG_LEN - 1] = '\0';

        bytes = send(sockfd, message, ((strlen(message)) + 1), 0);
        if (bytes < 0) {
            printf("Error sending message to server\n");
            close(sockfd);
            exit(EXIT_FAILURE);
        }

        if (0 == strncmp(message, "exit", 4)) {
            printf("Exiting..\n");
            close(sockfd);
            exit(EXIT_SUCCESS);
        }

        memset(message, 0, sizeof(message));

        bytes = recv(sockfd, message, sizeof(message), 0);
        if (bytes < 0) {
            printf("Error reading from socket\n");
            close(sockfd);
            exit(EXIT_FAILURE);
        }
        message[MSG_LEN - 1] = '\0';

        printf("Reply from server: %s\n", message);
    }

    exit(EXIT_SUCCESS);
}
