/*client*/
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

#define MYPORT 8887
#define BUFFER_SIZE 1024

int sock_cli;

void *send_data(void *data)
{
    int len;
    char buffer[BUFFER_SIZE];
    while (1)
    {
        len = recv(sock_cli, buffer, sizeof(buffer), 0);
        if (strcmp(buffer, "exit\n") == 0)
            break;
        fputs(buffer, stdout);
        usleep(1000);
    }
}

void *recev_data(void *data)
{
    char sendbuf[BUFFER_SIZE];
    int len;
    while (1)
    {
        fgets(sendbuf, sizeof(sendbuf), stdin);

        send(sock_cli, sendbuf, 1024, 0);
        usleep(1000);
    }
}

int main()
{
    ///定义sockfd
    pthread_t th_a, th_b;
    void *retval;

    sock_cli = socket(AF_INET, SOCK_STREAM, 0);

    ///定义sockaddr_in
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(MYPORT);                 ///服务器端口
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); ///服务器ip

    ///连接服务器，成功返回0，错误返回-1
    if (connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("connect");
        exit(1);
    }

    char sendbuf[BUFFER_SIZE];
    char recvbuf[BUFFER_SIZE];

    pthread_create(&th_a, NULL, send_data, 0);
    pthread_create(&th_b, NULL, recev_data, 0);

    pthread_join(th_a, &retval);
    pthread_join(th_b, &retval);

    close(sock_cli);
    return 0;
}
