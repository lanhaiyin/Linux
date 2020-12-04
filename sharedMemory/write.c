#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>

int main()
{
    //创建共享内存
    int shmid=shmget(0x99999999,1,IPC_CREAT|0664);
    if(shmid<0)
    {
        perror("shmid");
        return 0;
    }
    //成功返回内存的操作句柄
    void *addr=shmat(shmid,NULL,0);
    if(!addr)
    {
        perror("shmat");
        return 0;
    }
    //往内存当中写入数据
    int count=0;
    while(1)
    {
        sleep(2);
        ++count;
       snprintf((char *)addr,1024,"%s--%d","mawenjie",count);
    }
    //分离进程
    shmdt(addr);
    //销毁内存
    shmctl(shmid,IPC_RMID,NULL);
        return 0;
}
