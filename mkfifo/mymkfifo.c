#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
int main()
{
  //创建命名管道
  int ret=mkfifo("./fifo",0664);
  if(ret<0)
  {
    //命名管道创建失败
    perror("mkfifo");
    return 0;
  }
 int fd= open("./fifo",O_WRONLY,0664);
 if(fd<0)
 {
   perror("open");
   return 0;
 }
 write(fd,"mawenjie",8);
 close(fd);
 return 0;
}
