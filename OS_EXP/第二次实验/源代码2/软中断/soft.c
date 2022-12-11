#include<stdio.h>
#include<sys/types.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
#include<wait.h>

int wait_flag;
void stop(){
	wait_flag = 0;
  }

int main() 
{
	int pid1,pid2;
	wait_flag = 1;
	signal(2,stop);
  //signal(3,stop);
	while(wait_flag == 1);
	while((pid1 = fork()) == -1);
	if(pid1>0) 
	{
		while((pid2 = fork()) == -1);
		if(pid2  >  0) 
		{
			wait_flag = 1;
			sleep(5);
			kill(pid1,14);//16 >>>14
			kill(pid2,17);
			wait(0);
			wait(0);
			printf("Parent process is killed !!\n");
			exit(0);
		}
		else 
		{
			wait_flag = 1;
			signal(17,stop);
			while(wait_flag == 1);
			printf("Child process 2 is killed by parent !!\n");
			exit(0);
		}
	}
    else 
    {
		wait_flag = 1;
		signal(14,stop);//16>>>14
		while(wait_flag == 1);
		printf("Child process 1 is killed by parent !!\n");
		exit(0);
	}
}


