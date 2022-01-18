#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <string.h>

void extract (char* src, char* dest, int start, int end){
    int i,j=0;
    int size = strlen(src);

    //strncpy(dest, src + start, end-start);
    //dest[end-start] = '\0';
}

int main() {

    MYSQL *conn= mysql_init(NULL);/*Create database link pointer*/
    if(conn == NULL) { /*If it returns NULL, the initialization failed*/
        printf("mysql_init failed!\n");
        return EXIT_FAILURE;
    }
/*The parameters are: conn, the connection handle, that is, the mysql pointer above; host or address where mysql is located, the default is "127.0.0.1";
user user name, passwd password, database_name database name, these three items are entered according to your own Mysql configuration; the latter are all default and do not need to be modified*/
    conn=mysql_real_connect(conn,"192.168.50.133","cTion_user","1234","cTion",3306,NULL,0);
    if (conn) {
        printf("\033[2;35m");
        printf("ConnecTion success!\n");
        printf("\033[0m");

        char name [25] = "Bonjour" ;
        char result [25];

        extract(name, result, 1, 5);

        //printf("\nresult : %s", result);

        return 0;

    }else{
        printf("Connection failed!\n");
    }


    return 0;
}
