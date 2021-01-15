#include <string>
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
using namespace std;
class tcp
{

    public:
        tcp()
        {
            _socket=-1;
        }
        ~tcp()
        {

        }
        //创建套接字
        bool create()
        {
            _socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
            if(_socket<0)
            {
                perror("socket");
                return false;
            }
            return true;
        }
        //绑定地址信息
        bool Bind(string ip,uint16_t port)
        {
           struct sockaddr_in addr;
           addr.sin_family=AF_INET;
           addr.sin_port=htons(port);
           addr.sin_addr.s_addr=inet_addr(ip.c_str());
           int ret=bind(_socket,(struct sockaddr*)&addr,sizeof(addr));
           if(ret<0)
           {
               perror("bind");
               return false;

           }
           return true;
        }
        //监听
        bool Listen(int backlog=5)
        {
            int ret=listen(_socket,backlog);
            if(ret<0)
            {
                perror("listen");
                return false;
            }
            return true;
        }
        //发起连接
        bool Connect(string &ip,uint16_t port)
        {
           struct sockaddr_in destaddr;
          destaddr.sin_family=AF_INET;
          destaddr.sin_port=htons(port);
           destaddr.sin_addr.s_addr=inet_addr(ip.c_str());
            int ret=connect(_socket,(struct sockaddr*)&destaddr,sizeof(destaddr));
            if(ret<0)
            {
                perror("connect");
                return false;
            }
            return true;
        }
        //接收连接
        bool Accept(struct sockaddr_in *peeraddr,tcp* _ts)
        {
            socklen_t addrlen=sizeof(struct sockaddr_in);
            int newsocket=accept(_socket,(struct sockaddr*)peeraddr,&addrlen);
            if(newsocket<0)
            {
                perror("accept");
                return false;
            }
            _ts->_socket=newsocket;
            return true;
        }
        //发送数据
        bool Send(string &data)
        {
            int ret=send(_socket,data.c_str(),data.size(),0);
            if(ret<0)
            {
                perror("sendto");
                return false;
            }
            return true;
        }
        //接收数据
        bool Recv(string* buf)
        {
            char temp[1024]={0};
            int recvsize=recv(_socket,temp,sizeof(temp)-1,0);
            if(recvsize<0)
            {
                perror("recvfrom");
                return false;
            }
            (*buf).assign(temp,recvsize);
            return true;
        }
        //关闭套接字
        bool Close()
        {
            int ret=close(_socket);
            if(ret<0)
            {
                perror("close");
                return false;

            }
            _socket=-1;
            return true;
        }
    private:
        int _socket;
};
