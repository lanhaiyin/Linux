#include "tcp.hpp"
#include <signal.h>
#include <sys/wait.h>
void sigcb(int signal)
{
    (void)signal;
    while(1)
    {
        waitpid(-1,NULL,WNOHANG);
    }
}
int main(int argc,char *argv[])
{
 string   ip=argv[1];
 uint16_t port=atoi(argv[2]);
 tcp ts;
 signal(SIGCHLD,sigcb);
 if(!ts.create())
 {
     return 0;
 }
 if(!ts.Bind(ip,port))
 {
     return 0;
 }
 if(!ts.Listen(5))
 {
     return 0;
 }
 while(1)
 {
    struct sockaddr_in clientaddr;
     tcp newts;
     if(!ts.Accept(&clientaddr,&newts))
     {
        continue;
     }
     cout<<"新来一个连接端口为"<<ntohs(clientaddr.sin_port)<<endl;
     //创建子进程让子进程进行收发数据，父进程专门用来接收连接
     
    int pid=fork();
     if(pid<0)
     {
         perror("fork");
         exit(1);
     }
    else if(pid==0)
    {
          //子进程
         //接收数据
         while(1)
          {
    string buf;
    newts.Recv(&buf);
    printf("client say:%s\n",buf.c_str());
    //发送数据
    printf("server say:");
    fflush(stdout);
    getline(cin,buf);
    newts.Send(buf);
        }
   
   newts.Close();
   exit(1);
    }
     else{
         newts.Close();
     }
 //ts.Close();
 }
 return 0;
}
