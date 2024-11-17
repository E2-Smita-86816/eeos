#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<unistd.h>
#include<sys/wait.h>
#include<signal.h>


#define SMKEY 0x1234
#define SIZE 5

typedef struct circular_queue{
	int front;
	int rear;
	int count;
	int arr[SIZE];
}cq_t;

cq_t *ptr;
int shmid;

void init_cq(cq_t *cq){
	memset(cq->arr,0,sizeof(cq->arr));
	cq->count=0;
	cq->front=-1;
	cq->rear=-1;
}

int full(cq_t *cq){
	return cq->count==SIZE;
}

int empty(cq_t *cq){
	return cq->count==0;
}

void enqueue(cq_t *cq,int data){
	cq->rear=(cq->rear+1)%SIZE;
	cq->arr[cq->rear]=data;
	cq->count++;
}

int dequeue(cq_t *cq){
	cq->front=(cq->front+1)%SIZE;
	cq->count--;
	return cq->arr[cq->front];
}

void sigchld_handler(int sig){
	int s;
	waitpid(-1,&s,0);
}

void sigint_handler(int sig){
	shmdt(ptr);
	shmctl(shmid,IPC_RMID,NULL);
	_exit(1);
}


int main(){
//	int shmid;
	int ret,pid;
	struct sigaction sa;
	memset(&sa,0,sizeof(sa));
	sa.sa_handler=sigint_handler;
	ret=sigaction(SIGINT,&sa,NULL);
	sa.sa_handler=sigchld_handler;
	ret=sigaction(SIGCHLD,&sa,NULL);
	

	shmid=shmget(SMKEY,sizeof(cq_t),IPC_CREAT | 0600);
	
	ptr=shmat(shmid,NULL,0);
	init_cq(ptr);
	
	pid=fork();
	if(pid==0){ //child
		while(1){
		int val=dequeue(ptr);
		printf("RD:%d\n",val);
		sleep(1);
		}
	}
	else{
	while(1){
		int val=rand()%100;
		enqueue(ptr,val);
		printf("WR:%d\n",val);
		sleep(1);
	}
	}
	
	return 0;
}
