#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "mysql.c"

int main(int argc, char **argv) {

    int state = 0, connected=0;

    MYSQL *conn= mysql_init(NULL);/*Create database link pointer*/

    connectBD(&state, conn, "n2o93bb1bwmn0zle.chr7pe7iynqr.eu-west-1.rds.amazonaws.com", "wbz6ulqh7s5afptp");
    initPrepareSql(conn);

    char pseudo[25]="test";

    getDoc (conn, pseudo);


}
