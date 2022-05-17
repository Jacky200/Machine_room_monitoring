#include "sqlite3.h"
#include "cgic.h"
#include <stdlib.h>
#include <stdio.h>

int cgiMain(){
    //打印HTTP协议头
    cgiHeaderContentType("text/html");
    char username[34];
    char password[34];
    sqlite3 *ppdb=NULL;
#if 1
    char *str=getenv("QUERY_STRING");
    if(str==NULL){
        perror("[getenv error]");
        return -1;
    }
    sscanf(str,"username=%[^&]&password=%s",username,password);
#else
    cgiFormString("username",username,33);
    cgiFormString("password",password,33);
#endif
    //打开数据库
    int ret=sqlite3_open("/home/jacky/www/sqlite3/my.db",&ppdb);
    if(ret!=SQLITE_OK){
        perror("open sqlite error");
        return -1;
    }
    //创建表
    char *sql="create table if not exists pwd(id integer NOT NULL PRIMARY KEY AUTOINCREMENT"
              ", username varchar(32) unique, password varchar(32))";
    char *error;
    ret=sqlite3_exec(ppdb,sql,NULL,NULL,&error);
    if(ret!=SQLITE_OK){
        printf("%s\n",error);
        sqlite3_free(error);
        sqlite3_close(ppdb);
        return -1;
    }
    sqlite3_free(error);
    error=NULL;
    //查询语句
    char select_sql[128]={0};
    sprintf(select_sql,"select * from pwd where username='%s' and password='%s' ",username,password);
    //使用非回调查询
    char **result=NULL;
    int row; //行
    int col; //列
    ret=sqlite3_get_table(ppdb,select_sql,&result,&row,&col,&error);
    if(ret!=SQLITE_OK){
        printf("%s\n",error);
        sqlite3_free(error);
        sqlite3_free_table(result);
        sqlite3_close(ppdb);
        return -1;
    }
    if(row>0){ //查到该用户
        fprintf(cgiOut,"1");
    }else{//未查到该用户
        fprintf(cgiOut,"0");
    }
    sqlite3_free(error);
    sqlite3_free_table(result);
    sqlite3_close(ppdb);
    error=NULL;
    result=NULL;
    ppdb=NULL;
    return 0;
}

