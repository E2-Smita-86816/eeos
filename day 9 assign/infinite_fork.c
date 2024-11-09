#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
    int pid ,cnt;

    while(1)
    {
        pid = fork();

        if(pid == -1)
        {
            printf("fork() faild !\n");
            waitpid((-1,NULL,0)>0); // clear process 
            exit(1);
        }
        else if(pid == 0)
        {
            _exit(0);
        }
        else
        {
            cnt++;
            printf("%d\n",cnt);
        }
    }
}