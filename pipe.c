#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
//关闭父子进程的读端，设置管道为非阻塞属性，让子进程去一直写，父进程进行等待获取子进程的状态
int main()
{
  int fd[2];

  int ret=pipe(fd);
  //fd[0]是读端，fd[1]是写端
  int flag=fcntl(fd[1],F_GETFL);
  flag|=O_NONBLOCK;
 //使得文件描述符设置为非阻塞的
 flag=fcntl(fd[1],F_SETFD,flag);
 int pid=fork();
 if(pid<0)
 {
   perror("fork");
   return 0;
 }
 else if(pid==0)
 {
   close(fd[0]);//关闭读端文件描述符
   write(fd[1],"123",3);

 }else{
   //father
   close(fd[0]);
   //父进程进行等待
   int status;
   wait(&status);
 printf("status:%d",status&0x7f);
 }


  return 0;
}
