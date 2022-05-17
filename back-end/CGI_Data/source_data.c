#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define file "/home/jacky/Work/Machine_room_monitoring/Data/01.txt"

//定义数据结构体
typedef struct data{
    char temperature_1[8];
    char temperature_2[8];
    char temperature_3[8];
    char temperature_4[8];
    char temperature_5[8];
}Data;

//文件描述符初始化
static int fd_init(char *filepath){
    int fd=0;
    fd=open(filepath,O_RDWR);
    if(fd<0){
        perror("get fd error\n");
        exit(-1);
    }
    //制作空洞文件
    lseek(fd,1024,SEEK_SET);
    write(fd,"0",1);
    return fd;
}

//mmap映射到空间
static Data * mmap_init(int fd){
    Data *res=(Data *)malloc(sizeof(Data));
    res=mmap(NULL,sizeof(Data),PROT_READ |PROT_WRITE,MAP_SHARED,fd,0);
    if(res==MAP_FAILED){
        perror("[mmap_init error]");
        exit(-1);
    }
    return res;
}

int main(int argc ,char **argv){
    //添加随机数种子
    srand((unsigned int)time(NULL));
    int fd=fd_init(file);
    Data *ptr=mmap_init(fd);
    printf("温度检测中.......\n");
    //循环产生随机数
    float t;
    while (1){
        t=(float )(rand()%4000)/100.0;
        gcvt(t,7,ptr->temperature_1);
        t=(float )(rand()%4000)/100.0;
        gcvt(t,7,ptr->temperature_2);
        t=(float )(rand()%4000)/100.0;
        gcvt(t,7,ptr->temperature_3);
        t=(float )(rand()%4000)/100.0;
        gcvt(t,7,ptr->temperature_4);
        t=(float )(rand()%4000)/100.0;
        gcvt(t,7,ptr->temperature_5);
        sleep(1);
    }
    return 0;
}
