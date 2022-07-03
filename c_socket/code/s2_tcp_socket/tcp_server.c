#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

void read_data(int listen_fd){
    int times = 0;
    long length = 0;
    char buf[1024];

    while(1) {
        int read_size = read(listen_fd, buf,1024);
        if (read_size < 0) {
            if (errno == EINTR) {
                continue;
            }else{
                return ;
            }
        }else if(read_size == 0) {
            break;
        }

        length += read_size;

        if (length >= 1024) {
            times++;
            length -= 1024;
            printf("1k read %d \n", times);
            usleep(1000);
        }
    }
}

int main(){
    int server_fd;
    int listen_fd;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        printf("socket failed");
        return -1;
    }

    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    bzero(&server_address,sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(12356);
    inet_pton(AF_INET,"127.0.0.1",&server_address.sin_addr);

    //bind
    bind(server_fd,(struct sockaddr *) &server_address, sizeof(server_address));
    //listen
    listen(server_fd,1024);

    while (1) {
        socklen_t client_len= sizeof(client_address);
        listen_fd = accept(server_fd,(struct sockaddr* ) &client_address, &client_len);
        read_data(listen_fd);
        close(listen_fd);
    }


    return 0;
}
