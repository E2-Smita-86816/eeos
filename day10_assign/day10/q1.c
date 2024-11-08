/**Input signal number and a process id from user. 
Send given signal to the given process using
kill() syscall.**/

#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
       #include <sys/types.h>
       #include <signal.h>


int main(){
	int n1;
	//int n2;
	printf("enter n1:\n");
	scanf("%d",&n1);

	int ret=kill(n1,SIGKILL);
	if(ret==-1){
		perror("kill failed..\n");
		exit(0);
	}
	printf("kill success with return as : %d",ret);
	return 0;
	}
