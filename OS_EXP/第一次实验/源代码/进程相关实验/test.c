#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main(){
    pid_t pid2;
    pid2 = getpid();
    printf("hello world, my pid is %d",pid2);
    return 0;
}