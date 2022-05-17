#include "cJSON.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define file "/home/jacky/Work/Machine_room_monitoring/Data/01.txt"

typedef struct data{
    char temperature_1[8];
    char temperature_2[8];
    char temperature_3[8];
    char temperature_4[8];
    char temperature_5[8];
}Data;

//文件描述符初始化
static int fd_init(char *filepath){
    int fd=open(filepath,O_RDONLY);
    if(fd<0){
        perror("[get fd error]");
        exit(-1);
    }
    //制作空洞文件


    lseek(fd,1024,SEEK_SET);
    write(fd,"0",1);
    return fd;
}

//mmap初始化
static Data *mmap_init(int fd){
    Data *res=(Data *)malloc(sizeof(Data));
    res=mmap(NULL,sizeof(Data),PROT_READ,MAP_SHARED,fd,0);
    if(res==MAP_FAILED){
        perror("[mmap_init error]");
        exit(-1);
    }
    return res;
}

int main(int argc ,char **argv){
    //打印HTTP协议头
    printf("Content-type: text/html\r\n");
    printf("\r\n");

    int fd=fd_init(file);
    //初始化文件描述符
    Data *ptr=mmap_init(fd);

    //转换成JSON格式
    //接收JSON
    char *res_json=NULL;
    //创建头指针
    cJSON *json_head=NULL;
    json_head=cJSON_CreateObject();
    //添加到JSON字符串中
    cJSON_AddStringToObject(json_head,"temperature1",ptr->temperature_1);
    cJSON_AddStringToObject(json_head,"temperature2",ptr->temperature_2);
    cJSON_AddStringToObject(json_head,"temperature3",ptr->temperature_3);
    cJSON_AddStringToObject(json_head,"temperature4",ptr->temperature_4);
    cJSON_AddStringToObject(json_head,"temperature5",ptr->temperature_5);

    res_json=cJSON_Print(json_head);
    printf("%s\n",res_json);
    return 0;
}
