#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
int main()
{
  
 int fd= open("./fifo",O_RDONLY,0664);
 if(fd<0)
 {
   perror("open");
   return 0;
 }
 char buf[1024];
 read(fd,buf,sizeof(buf)-1);
 
 printf("%s\n",buf);
 close(fd);
 return 0;
}
