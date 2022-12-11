#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>

void *thread_one()
{  
   char *filename[]={"./test2",NULL};
   char *envp[]={0,NULL};
   execve("/usr/local/src/test2",filename,envp);
//   printf("thread_one:int %d main process, the tid=%lu,pid=%ld,  var = %d \n",getpid(),pthread_self(),syscall(SYS_gettid),var);
}

void *thread_two()
{   //system fucn
    system("cal");
    system("ls");
    
    printf("thread_two:int %d main process, the tid=%lu,pid=%ld, \n",getpid(),pthread_self(),syscall(SYS_gettid));
}

int main(int argc, char *argv[])
{
    
    pid_t pid;
    pthread_t tid_one,tid_two;
    
    if((pid=fork())==-1)// fork failed
    {
        printf("fork failed!");
        exit(EXIT_FAILURE);
    }                  
    

    else if(pid==0) // child progress
    {
        pthread_create(&tid_one,NULL,(void *)thread_one,NULL);
        pthread_join(tid_one,NULL);
    }
    else           //parent progress
    {
        pthread_create(&tid_two,NULL,(void *)thread_two,NULL);
        pthread_join(tid_two,NULL);
    }
    wait(NULL);
    return 0;
}