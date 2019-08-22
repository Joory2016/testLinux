#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(){
    char buff[255]={};
    int fd[2];      //文件描述符
    pid_t pid;
    //返回值，若成功返回0，失败返回-1
    if(pipe(fd)<0){     //创建管道
        perror("pipe");
        return -1;
    }

    //赋值运算符比比较运算符优先级低
    if((pid=fork())<0){         //创建子进程
        perror("fork");
        return -1;
    }  
    else if(pid==0){            //子进程
        printf("\npid:%d\n",getpid());
        close(fd[1]);
        while(1){
            sleep(1);
            read(fd[0],buff,20);
            printf("rev: %s\n",buff);
            bzero(0,sizeof(buff));
            getchar();
        }
    } 
    else{
        close(fd[0]);
        write(fd[1],"hahaha...",12);
    }

    return 0;
}