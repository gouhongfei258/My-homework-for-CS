#include <stdio.h>
#include <string.h>
#include "main.h"
#include "init.h"

int main(int argc,char **argv)
{
    char command[10],temp[9];
    initialize_memory();
    while(1)
    {

        printf("%s]#",current_path);
        scanf("%s",command);
        if(!strcmp(command,"cd")) //进入当前目录下
        {
            scanf("%s",temp);
            cd(temp);
        }
        else if(!strcmp(command,"mkdir"))  //创建目录
        {
            scanf("%s",temp);
            mkdir(temp,2);
        }
        else if(!strcmp(command,"touch"))    //创建文件
        {
            scanf("%s",temp);
            cat(temp,1);
        }

        else if(!strcmp(command,"rmdir"))  //删除空目录
        {
            scanf("%s",temp);
            rmdir(temp);
        }
        else if(!strcmp(command,"rm"))     //删除文件或目录，不提示
        {
            scanf("%s",temp);
            del(temp);
        }
        else if(!strcmp(command,"open"))    //打开一个文件
        {
            scanf("%s",temp);
            open_file(temp);
        }
        else if(!strcmp(command,"close"))   //关闭一个文件
        {
            scanf("%s",temp);
            close_file(temp);
        }
        else if(!strcmp(command,"read"))    //读一个文件
        {
            scanf("%s",temp);
            read_file(temp);
        }
        else if(!strcmp(command,"write"))   //写一个文件
        {
            scanf("%s\n",temp);
            write_file(temp);
        }
        else if(!strcmp(command,"ls"))      //显示当前目录
        {
        	ls();
        }
        else if(!strcmp(command,"format"))  //格式化硬盘
        {
            char tempch;
            printf("Format will erase all the data in the Disk\n");
            printf("Are you sure?y/n:\n");
            fflush(stdin);
            scanf(" %c",&tempch);
            if(tempch=='Y'||tempch=='y')
            {
                format();
            }
            else
            {
            	printf("Format Disk canceled\n");
            }
        }
        else if(!strcmp(command,"ckdisk"))  //检查硬盘
        {
        	check_disk();
        }
        else if(!strcmp(command,"quit"))    //退出系统
        {
        	break;
        }
        else printf("No this Command,Please check!\n");
        getchar();
        
    }
    return 0;
}



