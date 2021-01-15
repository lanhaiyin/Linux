#include "tcp.hpp"
#include <pthread.h>
void* ThreadStart(void * arc)
{
//线程分离
pthread_detach(pthread_self());
    tcp *newts=(tcp *)arc;
    while(1)
    {
    string buf;
    newts->Recv(&buf);
    printf("client say:%s\n",buf.c_str());
    //发送数据
    printf("server say:");
    fflush(stdout);
    getline(cin,buf);
    newts->Send(buf);
    }
    newts->Close();
    delete newts;
    return NULL;
}

int main(int argc,char *argv[])
{
 string   ip=argv[1];
 uint16_t port=atoi(argv[2]);
 tcp ts;
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
     tcp *newts=new tcp();
     if(!ts.Accept(&clientaddr,newts))
     {
        continue;
     }
     cout<<"新来一个连接端口为"<<ntohs(clientaddr.sin_port)<<endl;
     //创建线程
     pthread_t tid;
     int ret=pthread_create(&tid,NULL,ThreadStart,(void*)newts);
    if(ret<0)
    {
        perror("pthread_create");
        return 0;
    }
 }
 return 0;
}
