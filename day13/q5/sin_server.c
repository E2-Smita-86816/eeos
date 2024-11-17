//server
//#include "sin.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>

#define SERV_ADDR   "172.18.7.16"
#define SERV_PORT   2709

int main(){
	int ret,serv_fd,client_fd;
	struct sockaddr_in serv_addr,client_addr;
	socklen_t socklen=sizeof(client_addr);
	//1.create server socket->socket(int socket_family, int socket_type, int protocol);
	serv_fd=socket(AF_INET,SOCK_STREAM,0);
	if(serv_fd<0){
		perror("socket fail");
		_exit(1);
	}
	//2.assign socket addr(ip+port no.)->bind(int sockfd, const struct sockaddr *addr,
  //              socklen_t addrlen);
     serv_addr.sin_family=AF_INET;
	 serv_addr.sin_port=htons(SERV_PORT);
	 //int inet_aton(const char *cp, struct in_addr *inp);
	 inet_aton(SERV_ADDR,&serv_addr.sin_addr);
	ret=bind(serv_fd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
	if(ret<0){
		perror("bind fail");
		_exit(1);
	}
	//3.int listen(int sockfd, int backlog);

	ret=listen(serv_fd,5);
	if(ret<0){
		perror("listen fail");
	}
	//6.accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
	//client_fd is designed to talk to client
	client_fd=accept(serv_fd,(struct sockaddr *)&client_addr,&socklen);
	if(client_fd<0){
		perror("client_fd fail");
	}
	char buf1[512];
	do{
	//8.read
	read(client_fd,buf1, sizeof(buf1));
	printf("client: %s\n",buf1);
	//9.write
	printf("server: ");
	gets(buf1);
	write(client_fd,buf1,sizeof(buf1));
	}while(strcmp(buf1,"bye")!=0);
	//12.close
	close(serv_fd);
	//13.shutdown
	ret=shutdown(serv_fd,SHUT_RDWR);
	if(ret<0){
		perror("shutdown fail");
	}
	return 0;
}
