#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>

int main(){
    pid_t pid2,pid3;
    pid2 = getpid(); 
    pid3 = syscall(SYS_gettid);
    printf("Im created by thread_one , my pid is %d thread_one pid is %d",pid2,pid3);
    return 0;
}