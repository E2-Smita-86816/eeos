//Write a program to ﬁnd the size of the pipe buﬀer.

#include <stdio.h>
#include <unistd.h>

int main() {
    int ret;
	int arr[2];
	char buf[1]={'x'};
	int pipesize=0;
	ret = pipe(arr);
	
    if(ret < 0) {
        perror("pipe() failed");
        _exit(1);
    }
    while(1){
	while((write(arr[1], buf, sizeof(buf)))!=-1){
    	pipesize++;
		printf("pipe buffer size:%d bytes\n",pipesize);
//		printf("h");
	}
	}
    close(arr[0]);
    close(arr[1]);
	
    return 0;
}
