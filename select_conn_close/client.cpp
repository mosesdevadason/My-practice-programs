#include <cstdio>
#include <cstring>
#include <iostream>

extern "C"
{
#include <errno.h>
#include <unistd.h>
#include <signal.h>

#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
}

#define STR_SIZE    (1024)
#define PORT_NUM    (12345)
#define SERVER_ADDR "127.0.0.1"

static volatile sig_atomic_t running = 1;

void sig_handler(int signum)
{
    running = 0;
}

int main(int argc, char *argv[])
{
    int                 sockfd = -1;
    char                buff[STR_SIZE] = {'0'};
    struct sockaddr_in  server_addr;
    struct              sigaction action;

    memset(static_cast<void *>(&action), 0, sizeof(struct sigaction));
    action.sa_handler = sig_handler;
    sigaction(SIGTERM, &action, NULL);
    sigaction(SIGINT, &action, NULL);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sockfd) {
        perror("socket() failed ");
        return 1;
    }

    memset(static_cast<void *>(&server_addr), 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    inet_pton(AF_INET, SERVER_ADDR, &server_addr.sin_addr);
    server_addr.sin_port = htons(PORT_NUM);

    if (-1 == connect(sockfd,
                      reinterpret_cast<const struct sockaddr *>(&server_addr),
                      sizeof(server_addr))) {
        perror("connect() failed");
        close(sockfd);
        return 1;
    }

    while(running) {
        memset(static_cast<void *>(buff), 0, sizeof(buff));
        printf("Enter msg to send to be sent to the server: ");
        std::cin.getline(buff, sizeof(buff));
        if (-1 == send(sockfd, buff, sizeof(buff), 0)) {
            perror("send() failed");
            break;
        }
        printf("Sent msg! successfully\n");
    }

    printf("Exiting client gracefully!");
    close(sockfd);

    return 0;
}
