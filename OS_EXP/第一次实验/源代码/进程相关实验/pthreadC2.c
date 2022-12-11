#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main(){
    pid_t pid, pid1;

    pid = fork();// create child process

    if (pid  < 0){//error 
        fprintf(stderr , "fork falied");
        return 1;}

    else if (pid == 0){//child thread
        //system("cal");
        //system("ls");
        char *filename[]={"./test",NULL};
        char *envp[]={0,NULL};
         
        
        
        pid1 = getpid();
        printf("child pid = %d",pid); 
        printf("child pid1 = %d",pid1);
        execve("/usr/local/src/test",filename,envp);}
    else {// parent thread
        
        
        pid1 = getpid();
        printf("parent pid = %d",pid);
        printf("parent pid1 = %d",pid1);
        wait(NULL);}
        return 0;
        
}