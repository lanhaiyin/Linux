#include "tcp.hpp"
int main(int argc,char *argv[])
{
 string ip=argv[1];
 uint16_t port=atoi(argv[2]);
 tcp ts;
 if(!ts.create())
 {
     return 0;
 }
 if(!ts.Connect(ip,port))
 {
     return 0;
 }
 while(1)
 {
    //发送数据
    printf("client say:");
    fflush(stdout);
    string buf;
    getline(cin,buf);
    ts.Send(buf);
    //接收数据
    ts.Recv(&buf);
    printf("server say:%s\n",buf.c_str());
 }
    ts.Close();
    return 0;
}
