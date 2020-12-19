#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
//#include <mutex>
//案例说明：多个线程访问同一个临界资源并对其进行操作，这个操作不是原子性的，程序出现二义性即出现线程安全的问题，
//所以要对临界资源进行保护，即加上互斥锁
//如果互斥量的值为1，表示资源可以访问，0表示不可以访问
//加锁时对互斥量当中的值进行-1操作，解锁时进行+1操作
//对互斥量当中的值进行操作是原子性的，底层原因是加锁时，内存当中的值（mutex)和寄存器当中的值（0）进行互换（exchg），
//交换之后判断寄存器当中的值是否为1，不为1则挂起等待，为一则已经加锁，此刻mutex已经变为0
//解锁时，直接将mutex的赋值为1，这一步肯定是原子性的，因为只有了加锁才能解锁，没有其他线程会跟你抢这一步的操作

int temp =100 ; //定义临时变量为100
#define threadcont 3 //线程的数量为3
//定义互斥锁
pthread_mutex_t lock;
void *childthread(void *arg)
{
    //加互斥锁
    pthread_mutex_lock(&lock);
  while(1)
  {
      if(temp>0)
      {
         
          --temp;
          printf("我是%p线程，temp为%d\n",pthread_self(),temp);
          pthread_mutex_unlock(&lock);
      sleep(2);
      }
      else
      {
          //解互斥锁，必须在所有的出口都解锁
          pthread_mutex_unlock(&lock);
          break;
      }
  }
  return NULL;
}
int main()
{
    //初始化互斥锁
    pthread_mutex_init(&lock,NULL);
    pthread_t thread[threadcont];


    //创建线程
    for(int i=0;i<threadcont;++i)
    {
     int ret=pthread_create(&thread[i],NULL,childthread,NULL);
     if(ret<0)
     {
         //创建线程失败
         perror("pthread_create");
         break;
     }
    }
    //线程等待，等待子线程，进行资源的回收
    for(int i=0;i<threadcont;++i)
    {
        pthread_join(thread[i],NULL);
    }
    //销毁互斥锁
    pthread_mutex_destroy(&lock);
    return 0;
}
