/**. Parent continously prints Sunbeam and Child continously
prints Infotech.
They should keep printing them one after another (not simultaneously).**/


#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <signal.h>
#include <string.h>

#define SEM_KEY     0x4321

union semun {
    int              val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  /* Buffer for IPC_INFO (Linux-specific) */
};

void sigchld_handler(int sig) {
    int s,semid;
    waitpid(-1, &s, 0);
	semctl(semid, 0, IPC_RMID);
}

int main() {
    int ret, i, semid;
    struct sigaction sa;
    union semun su;
    struct sembuf ops[1];

    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = sigchld_handler;
    ret = sigaction(SIGCHLD, &sa, NULL);

    // create a semaphore with single counter
    semid = semget(SEM_KEY, 1, IPC_CREAT|0600);

    // initialize sema counter = 0
    su.val = 0;
    ret = semctl(semid, 0, SETVAL, su);
	while(1){
    ret = fork();
    if(ret == 0) {// child process -- print SUNBEAM
        char *str = "SUNBEAM\n";
        for(i=0; str[i]!='\0'; i++) {
            write(1, &str[i], 1); // print 1 char to stdout
            sleep(1);
        }
        // V(s);
        ops[0].sem_num = 0;
        ops[0].sem_op = +1;
        ops[0].sem_flg = 0;
        ret = semop(semid, ops, 1);
        // ...
        _exit(0);
    }
    else {// parent process -- print INFOTECH
        char *str = "INFOTECH\n";
        // P(s);
        ops[0].sem_num = 0;
        ops[0].sem_op = -1;
        ops[0].sem_flg = 0;
        ret = semop(semid, ops, 1);

        for(i=0; str[i]!='\0'; i++) {
            write(1, &str[i], 1); // print 1 char to stdout
            sleep(1);
        }
	}
        // ...

        // destroy semaphore
        //semctl(semid, 0, IPC_RMID);
    }
    return 0;
}
