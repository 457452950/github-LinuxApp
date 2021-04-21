/*server*/
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>

#include <time.h>
#include <pthread.h>

#define MYPORT 8887
#define QUEUE 20
#define BUFFER_SIZE 1024

int conn;
void *recev_data(void *data)
{
    char buffer[BUFFER_SIZE];
    while (1)
    {
        recv(conn, buffer, sizeof(buffer), 0);
        fputs(buffer, stdout);
        usleep(1000);
    }
}

void *send_data(void *data)
{
    char sendbuf[BUFFER_SIZE];
    while (1)
    {
        fgets(sendbuf, sizeof(sendbuf), stdin);
        send(conn, sendbuf, 1024, 0);
        usleep(1000);
    }
}

int main()
{
    char buffer[BUFFER_SIZE];
    struct sockaddr_in client_addr;
    socklen_t length;

    int fork_id;

    pthread_t th_a, th_b;
    void *retval;

    ///定义sockfd
    int server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    ///定义sockaddr_in
    struct sockaddr_in server_sockaddr;
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(MYPORT);
    server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    ///bind，成功返回0，出错返回-1
    if (bind(server_sockfd, (struct sockaddr *)&server_sockaddr, sizeof(server_sockaddr)) == -1)
    {
        perror("bind");
        exit(1);
    }

    ///listen，成功返回0，出错返回-1
    if (listen(server_sockfd, QUEUE) == -1)
    {
        perror("listen");
        exit(1);
    }

    ///客户端套接字

    length = sizeof(client_addr);

    ///成功返回非负描述字，出错返回-1
    while (1)
    {

        conn = accept(server_sockfd, (struct sockaddr *)&client_addr, &length);
        if (conn < 0)
        {
            perror("connect");
            exit(1);
        }
        fork_id = fork();
        if (fork_id == 0)
        {
            pthread_create(&th_a, NULL, send_data, 0);
            pthread_create(&th_b, NULL, recev_data, 0);

            pthread_join(th_a, &retval);
            pthread_join(th_b, &retval);
        }
    }
}
