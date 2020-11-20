#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
  int ret=fork();
  if(ret<0)
  {
    perror("fork");
  }
 else if(ret==0)
  {
    //返回给子进程，getpid为子进程的
    printf("child pid:%d, ret:%d ppid:%d\n",getpid(),ret,getppid());
    
  }
 else
  printf("father pid:%d, ret:%d  ppid:%d\n",getpid(),ret,getppid());
//  printf("pid:%d\n",getpid());
//  printf("pid:%d\n",getppid());//父进程的pid
sleep(1);
 return 0;
}
