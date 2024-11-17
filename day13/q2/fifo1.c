#include <fcntl.h>              /* Obtain O_* constant definitions */
       #include <unistd.h>
#include<stdio.h>

int main(){
	int ret;
	char buf1[64];
	ret=open("/home/manish/desd/eos/system_calls_programs/myfifo",O_WRONLY);
	if(ret<0){
		perror("open fail\n");
		_exit(1);
	}
	printf("p1:enter message to be sent");
	gets(buf1);
	ret=write(ret,buf1,sizeof(buf1));
	printf("p1:msg sent of %d bytes\n",ret);
	close(ret);
	return 0;
}
