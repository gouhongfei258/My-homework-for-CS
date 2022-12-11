#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>
int  global = 0;
int main(){
    
    pid_t pid, pid1;

    pid = fork();// create child process
    
    if (pid  < 0){//error 
        fprintf(stderr , "fork falied");
        return 1;}

    else if (pid == 0){//child thread
        global++;
        printf("value of glb is: %d",global);
        printf("addr of glb is: %d",&global);
        pid1 = getpid();
        printf("child pid = %d",pid);  // A process
        printf("child pid1 = %d",pid1);} // B process
    else {// parent thread
        global--;
        printf("value of glb is: %d",global);
        printf("addr of glb is: %d",&global);
        pid1 = getpid();
        printf("parent pid = %d",pid); // C process
        printf("parent pid1 = %d",pid1); // D process
    //    wait(NULL);}
        return 0;
        
}