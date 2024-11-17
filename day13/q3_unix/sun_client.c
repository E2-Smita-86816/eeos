//client
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>

#define SOCK_FILE   "/tmp/mysock"

typedef struct msg{
	int d1;
	int d2;
	int res;
}msg_t;

int main() {
    int ret, cli_fd;
    struct sockaddr_un serv_addr;
    msg_t m;
    //4. create client socket
    cli_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    //5. connect to server socket
    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, SOCK_FILE);
    ret = connect(cli_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
   // do {
        //7. send data to server
        printf("client: enter data1: ");
		scanf("%d",&m.d1);
		printf("client: enter data2: ");
		scanf("%d",&m.d2);
        
        write(cli_fd,&m,sizeof(msg_t));
        //10. read data from server
        read(cli_fd,&m, sizeof(msg_t));
        printf("server: %d is sum\n", m.res);
    //}while(strcmp(msg, "bye")!=0);
    //11. close client socket
    close(cli_fd);
    return 0;
}

