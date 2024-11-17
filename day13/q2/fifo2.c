#include <fcntl.h>              /* Obtain O_* constant definitions */
       #include <unistd.h>
#include<stdio.h>

int main(){
	int ret;
	char buf2[64];
	ret=open("/home/manish/desd/eos/system_calls_programs/myfifo",O_RDONLY);
	if(ret<0){
		perror("open fail\n");
		_exit(1);
	}
	printf("p2:waiting for p1 msg...\n");
	ret=read(ret,buf2,sizeof(buf2));
	printf("p2:msg recieved of %d bytes=%s\n",ret,buf2);
	close(ret);
	return 0;
}
