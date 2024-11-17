//client process
#include <fcntl.h>              /* Obtain O_* constant definitions */
       #include <unistd.h>
#include<stdio.h>

typedef struct msg{
	int d1;
	int d2;
	int res;
}msg_t;

int main(){
	int ret,ret1,ret2;
	int d1,d2;
	ret=open("/home/manish/desd/eos/eos_assignments/day13//myfifo",O_RDWR);
	if(ret<0){
		perror("open fail\n");
		_exit(1);
	}
	msg_t s;
	printf("p1:enter d1 to be sent");
	scanf("%d",&s.d1);
	printf("p1:enter d2 to be sent");
	scanf("%d",&s.d2);
	
	ret1=write(ret,&s,sizeof(msg_t));
	printf("p1:msg sent of %d bytes\n",ret1);
	close(ret1);
	ret2=read(ret,&s,sizeof(msg_t));
	printf("res is:%d\n",s.res);
	close(ret2);
	return 0;
}
