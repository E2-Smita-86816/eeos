#include "rectangle.h"
#include "square.h"
#include "circle.h"
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>


int main(){
	int err,pid1,pid2,pid3,s1,s2,s3;

	pid1=fork();
	if(pid1==0){
	//	printf("square area=%d\n",sq_area(5));
	//	sleep(1);
		_exit(0);
	}
	else{
		waitpid(pid1,&s1,0);
	}
	pid2=fork();
	if(pid2==0){
	//	printf("rectangle area=%d\n",rect_area(2,3));
	//	sleep(1);
		_exit(0);
	}
	else{
		waitpid(pid2,&s2,0);
	}
	pid3=fork();
	if(pid3==0){
	//	printf("circle area=%.2d\n",cir_area(2));
	//	sleep(1);
		_exit(0);
	}
	else{
		waitpid(pid3,&s3,0);
	}
	
	if(WEXITSTATUS(s1)==0){
		if(WEXITSTATUS(s2)==0){
			if(WEXITSTATUS(s3)==0){
				char *args[]={"gcc","-o","program.out","circle.o","square.o","rectangle.o","main.o",NULL};
				err=execvp("./program.out",args);
				if(err==-1){
					printf("exec failed\n");
				}
			}
		}
	}

	return 0;
}
