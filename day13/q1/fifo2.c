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
	char buf2[64];
	msg_t s;
	s.res=0;
	ret=open("/home/manish/desd/eos/eos_assignments/day13//myfifo",O_RDWR);
	if(ret<0){
		perror("open fail\n");
		_exit(1);
	}
	printf("p2:waiting for p1 msg...\n");
	ret1=read(ret,&s,sizeof(msg_t));
	printf("p2:msg recieved of %d bytes and numbers are %d,%d\n",ret,s.d1,s.d2);
	close(ret1);
	s.res=s.d1+s.d2;
	ret2=write(ret,&s,sizeof(msg_t));
	printf("p2:msg sent of %d bytes\n",ret2);
	close(ret2);
	return 0;
}
