//#include "mq.h"
/**Create message queue to send the ﬁfo name and ﬁle name from client to server. Send given ﬁle to the client via the given ﬁfo. Client should accept that
ﬁle and save to disk.**/
/***************************************CLIENT**************************************/
#include <stdio.h>
   #include <unistd.h>
   #include <sys/wait.h>
   #include <sys/msg.h>
   #include<sys/ipc.h>

 #define MQKEY 0X1234
 #define ID1 101
 #define ID2 201
  
  typedef struct msg{
     long id;
 char data[32];
}msg_t;
  

int main(){
	int ret,mqid;
	mqid=msgget(MQKEY,IPC_CREAT | 0600);
	if(mqid<0){
		perror("P1:msgget failed");
		_exit(1);
	}
	msg_t m1;
	m1.id=ID1;
	printf("P1:enter msg:");
	gets(m1.data);

	ret=msgsnd(mqid,&m1,sizeof(msg_t)-sizeof(long),0);
	if(ret<0){
		perror("P1:msgsnd fail");
	}
	else{
		printf("P1: msg sent:%s",m1.data);
	}

	printf("P1 waiting for P2 msg\n");
	msg_t m4;
	ret=msgrcv(mqid,&m4,sizeof(msg_t)-sizeof(long),ID2,0);
	
	if(ret<0){
		perror("P1:msgrcv fail");
	}
	else{
		printf("P1: msg received:%s",m4.data);
	}

	msgctl(mqid,IPC_RMID,0);

	return 0;
	}
