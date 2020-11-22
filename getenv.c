#include<unistd.h>
#include<iostream>
using namespace std;
//三种方式获取环境变量
//1.main函数的参数获取环境变量
#if 0
int main(int argc,char*argv[],char* env[])
{
  //argc命令行参数的个数
  //argc命令行参数的具体内容
  //env  环境变量
  for(int i=0;i<argc;++i)
  {
    cout<<argv[i]<<endl;
  }
  //直接打印环境变量
  for(int i=0;env[i];++i)
  {
    cout<<env[i]<<endl;
  }
#endif
#if 0

  //第二种方式 libc库当中提供的变量来获取
  int main()
  {

  
  extern char**environ;
  for(int i=0;environ[i];++i)
  {
    cout<<environ[i]<<endl;
   }
  return 0;
}
#endif
#include <stdlib.h>
//libc 库当中提供的函数来获取环境变量
//char* getenv(const char *name)
//name:环境变量的名称
//返回值：具体变量所对应的值
int main()
{
  char *path=getenv("PATH");
  cout<<path<<endl;
  return 0;
}
