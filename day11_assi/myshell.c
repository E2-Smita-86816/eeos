//Improve your shell program so that it should not be terminated due to SIGINT (ctrl+C).
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include<signal.h>

void sig_handler(int s){
	printf("signal caught:%d ,use 'exit' to quit\n",s);
}
int main(){
	int i,s,ret,err;
	char cmd[512],*ptr,*args[32];
	struct sigaction sa;
	memset(&sa,0,sizeof(struct sigaction));
	sa.sa_handler=sig_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags=0;
	ret=sigaction(SIGINT,&sa,NULL);
	if(ret<0){
		perror("sigaction fail\n");
		_exit(0);
	}

	while(1){
		printf("cmd> ");
		fgets(cmd,sizeof(cmd),stdin);
		strtok(cmd,"\n");
		int i=0;
		ptr=strtok(cmd," ");
		args[i]=ptr;
		i++;
		do{
			ptr=strtok(NULL," ");
			args[i]=ptr;
			i++;
		}while(ptr!=NULL);

		if(strcmp(args[0],"exit")==0)
			_exit(0);
		else if(strcmp(args[0],"cd")==0)
			chdir(args[1]);
		else{
			ret=fork();
			if(ret==0){
				err=execvp(args[0],args);
				if(err<0){
					perror("exec failed..\n");
					_exit(1);
				}
				else
					waitpid(ret,&s,0);
			}
		}
	}

	return 0;
}
