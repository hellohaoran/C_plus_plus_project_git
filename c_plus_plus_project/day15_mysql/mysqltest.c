#include<c43func.h>
#include<mysql/mysql.h> // 在/usr/include/mysql/mysql.h 目录下;
int main(){

MYSQL * conn = NULL;
char *host = "localhost";
char *user = "root";
char *passwd = "123";
char *db = "c43th";
// 1.获取与mysql服务器链接的句柄
conn = mysql_init(NULL) ; // 对MYsql句柄进行初始化
// 2. 与mysql服务器进行链接(TCP链接, 完成了三次握手的过程, 还有信息的校验过程); 
if(mysql_real_connect(conn,host,user,passwd, db,0,NULL,0) == NULL){// 连接失败
printf("error : %s\n", mysql_error(conn));
return EXIT_FAILURE; 
}
// 3. 对数据库进行查询
char * query = "select * from student";
int ret = mysql_query(conn,query); 
if(ret != 0){
    printf("error query :%s\n", mysql_error(conn));
    return EXIT_FAILURE;
}
//4.获取结果集
// use_result返回一个初始化结果集 ,但需要与fetch_row联合使用才能获取查询结果
// mysql_store_result 会将结果直接存在客户端
MYSQL_RES * result = mysql_use_result(conn);
 if(result == NULL){
    printf("error query :%s\n", mysql_error(conn));
    return EXIT_FAILURE;
}

// 获取行数 和 列数
int rows = mysql_num_rows(result);
int cols = mysql_num_fields(result);

printf("row = %d , col = %d\n", rows, cols);



//5. 获取一行数据
MYSQL_ROW fet_res = mysql_fetch_row(result); // 返回值是一个数组字符串;
// if(fet_res == )
// 获取每一行数据
while((fet_res = mysql_fetch_row(result))  != NULL){
for(int i =0; i<cols;++i){
    printf("%10s", fet_res[i]); 
}
puts(""); 
}


//6.关闭结果集和关闭连接
mysql_free_result(result);
mysql_close(conn); 
}