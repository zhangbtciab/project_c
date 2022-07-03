#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

#define SIZE 1024000
void send_data(int client_fd){
    char *data;
    data = (char *) malloc(sizeof(char) * (SIZE + 1 ));
    for (int i = 0; i < SIZE; ++i) {
        data[i] = 'a';
    }
    data[SIZE] = 0;

    int remain = strlen(data);
    const char* sendmsg = data;

    while(remain >= 0) {
        int written = send(client_fd, send, remain, 0);
        if (written < 0) {
            printf("发送失败 !");
            return;
        } else if(written == 0) {
            printf("发送完成 !");
            return;
        }

        remain -= written;
        sendmsg += written;

    }
    free(data);
    return;
}

int main(){
    int client_fd;

    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd < 0) {
        printf("socket failed");
        return -1;
    }

    struct sockaddr_in server_address;
    bzero(&server_address,sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(12356);
    inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);

    //connect
    int connect_flag = connect(client_fd,(struct sockaddr *) &server_address, sizeof(server_address));
    if (connect_flag < 0) {
        printf("连接失败");
        return -1;
    }

    send_data(client_fd);

    return 0;
}
