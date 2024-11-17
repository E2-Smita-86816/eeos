/**One thread prints "SUNBEAM" continuously, and other thread prints
"INFOTECH" continhously. Only one should print at a time starting with
"SUNBEAM". Hint: using condition variables.**/


#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

//sunbeam
//infotech
pthread_mutex_t m;
pthread_cond_t c;
int flag=0;
//thread fun1
void * fun1(void * params){
    while(1){
	//lock
    pthread_mutex_lock(&m);
    char *str="sunbeam\n";
	while(flag!=0){
          pthread_cond_wait(&c,&m);
    }
    for(int i=0;str[i]!='\0';i++){
        //printf("%c",str[i]);
        write(1,&str[i],1);
        sleep(1);
    }
    flag=1;
    //unlock
    pthread_cond_signal(&c);
    pthread_mutex_unlock(&m);
	}
    return NULL;
}

//thread fun2
void * fun2(void *params){
    while(1){
    pthread_mutex_lock(&m);
    while(flag!=1){
        pthread_cond_wait(&c,&m);
    }
	char *str="infotech\n";
    for(int i=0;str[i]!='\0';i++){
        //printf("%c",str[i]);
        write(1,&str[i],1);
        sleep(1);
    }
    flag=0;
	pthread_cond_signal(&c);
    //unlock
    pthread_mutex_unlock(&m);
	}
    return NULL;
}

int main(){
    int ret;
    pthread_t t1,t2;
    pthread_mutex_init(&m,NULL);
	
    pthread_create(&t1,NULL,fun2,NULL);
    pthread_create(&t2,NULL,fun1,NULL);
	
    printf("press enter to exit...\n");
    getchar();
    pthread_mutex_destroy(&m);
    pthread_cond_destroy(&c);
    return 0;
}



