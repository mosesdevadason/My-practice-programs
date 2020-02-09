#include <cstdio>
#include <cstring>
#include <algorithm>

extern "C"
{
#include <errno.h>
#include <unistd.h>
#include <signal.h>

#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
}

#define STR_SIZE   (1024)
#define PORT_NUM   (12345)
#define BACKLOG    (1)
#define INVALID_FD (-1)

static volatile sig_atomic_t running = 1;

void sig_handler(int signum)
{
    running = 0;
}

int main(int agrc, char *argv[])
{
    int                 server_fd = INVALID_FD;
    int                 client_fd = INVALID_FD;
    char                buff[STR_SIZE] = {'\0'};
    struct sockaddr_in  server_addr;
    struct sockaddr_in  client_addr;
    socklen_t           client_addr_len = 0;
    fd_set              rd;
    int                 max_fd = 0;
    int                 rc = 0;
    struct              sigaction action;

    memset(static_cast<void *>(&action), 0, sizeof(struct sigaction));
    action.sa_handler = sig_handler;
    sigaction(SIGTERM, &action, NULL);
    sigaction(SIGINT, &action, NULL);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == server_fd) {
        perror("socket() failed");
        return 1;
    }

    memset(static_cast<void *>(&server_addr), 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT_NUM);

    if (-1 == bind(server_fd,
                   reinterpret_cast<const struct sockaddr *>(&server_addr),
                   sizeof(server_addr))) {
        perror("bind() failed");
        close(server_fd);
        return 1;
    }

    if (-1 == listen(server_fd, BACKLOG)) {
        perror("listen() failed");
        close(server_fd);
        return 1;
    }

    FD_ZERO(&rd);
    while(running) {
        max_fd = std::max(server_fd, client_fd) + 1;
        FD_SET(server_fd, &rd);
        if (-1 != client_fd)
            FD_SET(client_fd, &rd);

        printf("Entering select...\n");
        rc = select(max_fd, &rd, nullptr, nullptr, nullptr);
        if (-1 == rc) {
            perror("select() failed");
            running = 0;
            continue;
        } else if (0 == rc) {
            printf("Timeout not set! Error!!\n");
            running = 0;
            continue;
        }

        // If server_fd is set, accept connection.
        if (FD_ISSET(server_fd, &rd)) {
            memset(static_cast<void *>(&client_addr), 0, sizeof(client_addr));
            client_fd = accept(server_fd,
                               reinterpret_cast<struct sockaddr *>(&client_addr),
                               &client_addr_len);
            printf("Accepted connection from client. Client fd = %d\n",
                   client_fd);
        }

        // If client FD is set, read from socket.
        if (0 != client_fd) {
            if (FD_ISSET(client_fd, &rd)) {
                rc = recv(client_fd, buff, sizeof(buff), 0);
                if (-1 == rc) {
                    perror("recv() failed");
                    running = 0;
                    continue;
                } else if (0 == rc) {
                    printf("Connection closed from remote end!\n");
                    running = 0;
                    continue;
                }
                printf("Msg Rx from client: %s\n", buff);
                memset(static_cast<void *>(buff), 0, sizeof(buff));
            }
        }
    }

    printf("Exiting server gracefully!\n");
    if (INVALID_FD == client_fd) {
        close(client_fd);
    }
    close(server_fd);

    return 0;
}
