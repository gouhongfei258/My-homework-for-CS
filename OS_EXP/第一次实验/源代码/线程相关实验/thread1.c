#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include<sys/types.h>
#include<string.h>
pthread_mutex_t mutex_lock;  //定义一个互斥全局名

void *thread_one(void* argv)
{  int c1 = 5000; int data1;
   memcpy(&data1, (int *)argv, sizeof(int));

pthread_mutex_lock(&mutex_lock); 
//lock

// 2 ways to change the data//
   for(;c1>=0; c1 --){ data1 ++;}  
  // for(;c1>=0; c1 --){ data1= 0;}
   

pthread_mutex_unlock(&mutex_lock);
//unlock
     printf("thread_one:int %d main process, the tid=%lu,pid=%ld  now a = %d \n",getpid(),pthread_self(),syscall(SYS_gettid),data1);
}

void *thread_two(void*argv)
{   int c2= 5000;  int data2;
    memcpy(&data2, (int *)argv, sizeof(int ));
pthread_mutex_lock(&mutex_lock); 
//lock
// 2 ways//
    for(;c2>=0; c2 --){ data2 --;}
//    for(;c2>=0;c2--){ data2= 1;}

pthread_mutex_unlock(&mutex_lock);
//unlock
    printf("thread_two:int %d main process, the tid=%lu,pid=%ld  now a = %d \n",getpid(),pthread_self(),syscall(SYS_gettid),data2);
}

int main(int argc, char *argv[])
{   
    int a =10;
    
    pid_t pid;
    pthread_t tid_one,tid_two;
    
	pthread_mutex_init(&mutex_lock,NULL); //init lock


    pthread_create(&tid_one,NULL,(void *)thread_one,(void *)&a);// create thread1
    

    pthread_create(&tid_two,NULL,(void *)thread_two,(void *)&a);// create thread2
    
    
    pthread_join(tid_one,NULL); //wait  thread1 
    pthread_join(tid_two,NULL); //wait thread2

    printf("final value of a is %d",a);

    return 0;
}