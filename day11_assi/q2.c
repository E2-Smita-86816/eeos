/**2. Implement asynchronous execution in your shell i.e.
if command suﬃxed with &, then shell should not wait for the child process.
Ensure that process isn't left zombie.**/
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include<signal.h>

void handle_sigchld(int sig) {
printf("exit status:%d\n",WEXITSTATUS(sig));
while (waitpid(-1, &sig , 0) > 0);
}

void sig_handler(int s){
	printf("signal caught:%d ,use 'exit' to quit\n",s);
}
int main(){
	int s,ret,err;
	char cmd[512],*ptr;
	char *args[32];
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
	sa.sa_handler = handle_sigchld; 
	sigemptyset(&sa.sa_mask); 
	sa.sa_flags = SA_RESTART; 
	if (sigaction(SIGCHLD, &sa, NULL) == -1)
	{ perror("sigaction"); 
	exit(1); 
	}
	while(1){
		printf("cmd> ");
		gets(cmd);	
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
			}
		}
	}

	return 0;
}
