#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>


int make_socket(uint16_t port) {
    int sockfd;
    struct sockaddr_in address;

    //创建套接字
    sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        printf("socket fail");
        exit(-1);
    }

    //绑定port和ip
    address.sin_family = AF_INET;//指定Ipv4协议
    address.sin_port = htons(port);//指定端口
    address.sin_addr.s_addr = htonl(INADDR_ANY);//通配地址

    if (bind(sockfd, (struct sockaddr*) &address, sizeof(address)) < 0) {
        printf("bind fail");
        exit(-1);
    }

    return sockfd;
}

int main(int grgc, char **grgv) {
    int sockfd = make_socket(12455);
    printf("%d",  sockfd);
    return 0;
}
