#include <stdio.h>
#include "sqlite3.h"
#include "cgic.h"
#include <stdlib.h>

int cgiMain(){
    //打印HTTP协议头
    cgiHeaderContentType("text/html");
    //获取账号和密码
    char username[34]={0};
    char password[34]={0};
    sqlite3 *ppdb=NULL;

#if 1
    //采用环境变量来解析Qt传输过来的数据
    char *str=getenv("QUERY_STRING");
    if(str==NULL){
        printf("arg error\n");
        return -1;
    }
    //解析环境变量username=xxx&password=xxxx
    sscanf(str,"username=%[^&]&password=%s",username,password);
#else
    //调用CGIC库来获取Qt传输的数据
    cgiFormString("username",username,33);
    cgiFormString("password",password,33);
#endif

    //打开数据库
    int ret=sqlite3_open("/home/jacky/www/sqlite3/my.db",&ppdb);
    if(ret!=SQLITE_OK){
        printf("open sqlite error");
        return -1;
    }
    //创建表
    char *sql="create table if not exists pwd(id integer NOT NULL PRIMARY KEY AUTOINCREMENT,"
              "username varchar(32)unique,password varchar(32))";
    char *error=NULL;
    ret=sqlite3_exec(ppdb,sql,NULL,NULL,&error);
    if(ret!=SQLITE_OK){
        printf("%s\n",error);
        sqlite3_free(error);
        sqlite3_close(ppdb);
        return -1;
    }
    sqlite3_free(error);
    error=NULL;
    //向表中插入数据
    char insert_sql[128]={0};
    sprintf(insert_sql,"insert into pwd(username,password) values('%s','%s')",username,password);
    ret=sqlite3_exec(ppdb,insert_sql,NULL,NULL,&error);
    if(ret!=SQLITE_OK){
        printf("%s\n",error);
        sqlite3_free(error);
        error=NULL;
        sqlite3_close(ppdb);
        fprintf(cgiOut,"0");
        return -1;
    }
    fprintf(cgiOut,"1"); //表示注册成功
    //关闭数据库
    sqlite3_free(error);
    sqlite3_close(ppdb);
    error=NULL;
    ppdb=NULL;
    return 0;
}



