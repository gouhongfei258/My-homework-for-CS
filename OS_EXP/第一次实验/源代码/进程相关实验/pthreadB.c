#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int  global = 10;
int main(){
    pid_t pid, pid1;
    
    pid = fork();// create child process
    
    if (pid  < 0){//error 
        fprintf(stderr , "fork falied");
        return 1;}

    else if (pid == 0){//child thread
        global++;
        printf("value of glb is: %d",global);
        pid1 = getpid();
        printf("child pid = %d",pid); 
        printf("child pid1 = %d",pid1);}
    else {// parent thread
        global--;
        printf("value of glb is: %d",global);
        pid1 = getpid();
        printf("parent pid = %d",pid);
        printf("parent pid1 = %d",pid1);
        wait(NULL);}
        
        global++;
        printf("value of glb is %d",global);
        return 0;
        
}