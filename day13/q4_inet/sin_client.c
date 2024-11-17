//client
//#include "sin.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>

#define SERV_ADDR   "127.0.0.1"
#define SERV_PORT   2809

typedef struct msg{
	int d1;
	int d2;
	int res;
}msg_t;

int main(){
	int ret,cli_fd;
	struct sockaddr_in serv_addr;
	//4.socket
//	int cli_fd;
	cli_fd=socket(AF_INET,SOCK_STREAM,0);
	if(cli_fd<0){
		perror("socket fail");
	}
	//5.connect(int sockfd, const struct sockaddr *addr,socklen_t addrlen);
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(SERV_PORT);
	inet_aton(SERV_ADDR,&serv_addr.sin_addr);
	
	ret=connect(cli_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	if(ret<0){
		perror("connect fail");
	}
	
	//do{
	//7.write
	msg_t m;
	printf("client: enter data1: ");
		scanf("%d",&m.d1);
		printf("client: enter data2: ");
		scanf("%d",&m.d2);
        
        write(cli_fd,&m,sizeof(msg_t));
        //10. read data from server
        read(cli_fd,&m, sizeof(msg_t));
        printf("server: %d is sum\n", m.res);
	//}while(strcmp(buf2,"bye")!=0);
	//11.close
	close(cli_fd);
	return 0;
}
