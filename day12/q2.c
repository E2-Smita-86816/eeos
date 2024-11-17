/**The child process send two numbers to the parent process via pipe.
The parent process calculate the sum and return via another pipe.
The child process print the result and exit.
The parent process wait for completion of the child and then exit.**/

#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include <fcntl.h>              /* Obtain O_* constant definitions */
#include<errno.h>

typedef struct msg{
	int n1;
	int n2;
	int res;
}msg_t;

void handle_EINTR() {
     if (errno == EINTR) {
         // Handle EINTR appropriately
         perror("System call interrupted by signal");
   }
 }

int main(){
	int p2c[2];
	//arr[0]->reader,arr[1]->writter
	int c2p[2];
	int ret,ret1,ret2,s;
	int res=0;
	msg_t m1,m2;
	ret1=pipe(p2c);
	if(ret1<0){
		perror("pipe fail\n");
		_exit(1);
	}
	ret2=pipe(c2p);
	if(ret2<0){
		perror("pipe fail\n");
		_exit(1);
	}
	ret=fork();
	if(ret==0){//child
		close(c2p[0]);
		close(p2c[1]);
		printf("c:enter first number:\n");	
		scanf("%d",&m1.n1);
		printf("c:enter second num:\n");
		scanf("%d",&m1.n2);
			
		write(c2p[1],&m1, sizeof(msg_t));
		printf("C:child written to pipe\n");
		read(p2c[0],&m2,sizeof(msg_t));
		printf("C:sum is %d\n",m2.res);
		close(c2p[1]);
		close(p2c[0]);
	}
	else{//parent
		close(p2c[0]);
		close(c2p[1]);
		printf("P:parent is waiting for msg from child\n");
		read(c2p[0],&m1,sizeof(msg_t));
		printf("p: the values sent by child are %d,%d\n ",m1.n1,m1.n2);

		m2.res=m1.n1+m1.n2;
		write(p2c[1],&m2,sizeof(msg_t));
		printf("P:parent sent data as m2.res=%d\n",m2.res);
		while(waitpid(ret,&s,0)==-1){
			handle_EINTR();
		}
		close(p2c[1]);
		close(c2p[0]);
	}



	return 0;
	}
