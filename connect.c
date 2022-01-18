#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>

/*
The program is a demonstration of using prepared statements to perform operations on the below table in mariadb.
The statements include: insert, select, delete, etc.

CREATE TABLE person (
  id integer primary key,
  name text,
  opaque blob);
*/

#define DB_CONN_STR "127.0.0.1"
#define DB_CONN_USER "root"
#define DB_CONN_PWD ""
#define DB_NAME "xhx"
#define INSERT_PERSON_STATEMENT "insert into person values (?, ?, ?)"
#define DELETE_ALL_PERSON_STATEMENT "delete from person"
#define DELETE_A_PERSON_STATEMENT "delete from person where id = ?"
#define SELECT_ALL_PERSON_STATEMENT "select * from person"

void err_exit(char* s);

MYSQL* gDbConn=NULL;
MYSQL_STMT* gInsertPersonStmt = NULL;
MYSQL_STMT* gDeleteAllPersonStmt = NULL;
MYSQL_STMT* gDeleteAPersonStmt = NULL;
MYSQL_STMT* gSelectAllPersonStmt = NULL;

MYSQL* initDb(){
    unsigned int timeout = 2;/*in second. unsigned int for this argument. */
    MYSQL* conn = mysql_init(NULL);
    if (conn == NULL) err_exit("init db failed");

    mysql_options(conn,MYSQL_OPT_CONNECT_TIMEOUT, &timeout );

     if (mysql_real_connect(conn,         /*MYSQL connection pointer*/
                       DB_CONN_STR,           /*DB Host*/
                       DB_CONN_USER,             /*DB User*/
                       DB_CONN_PWD,                          /*DB password*/
                       "xhx",     /*DB name*/
                           0,                            /*DB port*/
                            NULL,                         /*DB unix socket*/
                             0                             /*DB client_flag*/
                              ) == NULL) {
        err_exit("db connect failed");
    }

    return conn;
}

void initPreparedStatements(MYSQL* conn){
    int result;
    unsigned long count;

    gInsertPersonStmt = mysql_stmt_init(conn);
    if (gInsertPersonStmt == NULL) err_exit("init stmt failed");
    result = mysql_stmt_prepare(gInsertPersonStmt, INSERT_PERSON_STATEMENT, strlen(INSERT_PERSON_STATEMENT));
    if (result != 0) err_exit("prepare stmt failed");
    count = mysql_stmt_param_count(gInsertPersonStmt);
    printf("there are %d parameters in the insert statements\n", count);

    gDeleteAPersonStmt = mysql_stmt_init(conn);
    if (gDeleteAPersonStmt == NULL) err_exit("init stmt failed");
    result = mysql_stmt_prepare(gDeleteAPersonStmt, DELETE_A_PERSON_STATEMENT, strlen(DELETE_A_PERSON_STATEMENT));
    if (result != 0) err_exit("prepare stmt failed");

    gDeleteAllPersonStmt = mysql_stmt_init(conn);
    if (gDeleteAllPersonStmt == NULL) err_exit("init stmt failed");
    result = mysql_stmt_prepare(gDeleteAllPersonStmt, DELETE_ALL_PERSON_STATEMENT, strlen(DELETE_ALL_PERSON_STATEMENT));
    if (result != 0) err_exit("prepare stmt failed");

    gSelectAllPersonStmt = mysql_stmt_init(conn);
    if (gSelectAllPersonStmt == NULL) err_exit("init stmt failed");
    result = mysql_stmt_prepare(gSelectAllPersonStmt, SELECT_ALL_PERSON_STATEMENT, strlen(SELECT_ALL_PERSON_STATEMENT));
    if (result != 0) err_exit("prepare stmt failed");

}

void deleteAllPerson(){
    int result;
    /* delete all persons */
    result = mysql_stmt_execute(gDeleteAllPersonStmt);
    if (result != 0) err_exit("execute stmt delete failed");
}

void deleteAPerson(long id) {
    MYSQL_BIND bind;/*there is 1 place holder in the prepared statements. */ 

    unsigned int array_size = 1; /* the number of row to insert */
    int result;

    memset(&bind, 0, sizeof(MYSQL_BIND));

    bind.buffer_type = MYSQL_TYPE_LONG;
    bind.buffer = &id;
    bind.is_null = 0;
    bind.length = 0;

    mysql_stmt_attr_set(gDeleteAPersonStmt, STMT_ATTR_ARRAY_SIZE, &array_size);
    result = mysql_stmt_bind_param(gDeleteAPersonStmt, &bind);
    if (result != 0) err_exit("bind stmt delete failed");
    result = mysql_stmt_execute(gDeleteAPersonStmt);
    if (result != 0) err_exit("execute stmt delete failed");
}

void insertPerson(long id, char* name, char* opaque ){
    /* (1) refer to https://mariadb.com/kb/en/library/bulk-insert-column-wise-binding/ */
    /* (2) refer to https://docs.oracle.com/cd/E17952_01/mysql-5.7-en/mysql-stmt-execute.html */
    /* At last, by my test, (2) works, but (1) does not work */

    MYSQL_BIND bind[3];/*there are 3 place holders in the prepared statements. */

    unsigned int array_size = 1; /* the number of row to insert? */
    unsigned long nameLen = strlen(name);
    unsigned long opaqueLen = strlen(opaque);
    int result;

    memset(bind, 0, sizeof(MYSQL_BIND)*3);

    bind[0].buffer_type = MYSQL_TYPE_LONG;
    bind[0].buffer = &id;
    bind[0].is_null = 0;
    bind[0].length = 0;

    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = name;
    bind[1].buffer_length = strlen(name);
    bind[1].length = &nameLen;

    bind[2].buffer_type = MYSQL_TYPE_BLOB;
    bind[2].buffer = opaque;
    bind[2].buffer_length = strlen(opaque);
    bind[2].length = &opaqueLen;

    mysql_stmt_attr_set(gInsertPersonStmt, STMT_ATTR_ARRAY_SIZE, &array_size);
    result = mysql_stmt_bind_param(gInsertPersonStmt, bind);
    if (result != 0) err_exit("bind stmt insert failed");
    result = mysql_stmt_execute(gInsertPersonStmt);
    if (result != 0) err_exit("execute stmt insert failed");
}

void selectAllPerson(){
    int numFields;
    char strName[100];
    char strOpaque[100];
    long lenName;
    long lenOpaque;
    long longResult;
    int result;
    int row;
    MYSQL_BIND bind[3]; /*used to get result, not to provide parameters*/
    MYSQL_FIELD *fields;
    MYSQL_RES *metaData;
    my_bool isNull[3];

    numFields = mysql_stmt_field_count(gSelectAllPersonStmt);
    printf("there are %d fields in person table\n",numFields);/*it is able to get the correct field count*/

    metaData = mysql_stmt_result_metadata(gSelectAllPersonStmt);
    if (metaData == NULL) err_exit("failed to get metadata");

    fields = mysql_fetch_fields(metaData);
    memset(bind,0,sizeof(MYSQL_BIND)*3);
    bind[0].buffer_type = fields[0].type;
    bind[0].buffer = &longResult;
    bind[0].is_null = &isNull[0];

    bind[1].buffer_type = fields[1].type;
    bind[1].buffer = strName;
    bind[1].buffer_length = 100;
    bind[1].is_null = &isNull[1];
    bind[1].length = &lenName;

    bind[2].buffer_type = fields[2].type;
    bind[2].buffer = strOpaque;
    bind[2].buffer_length = 100;
    bind[2].is_null = &isNull[2];
    bind[2].length = &lenOpaque;


    result = mysql_stmt_bind_result(gSelectAllPersonStmt, bind);
    if (result!=0) err_exit("bind result failed");

    result = mysql_stmt_execute(gSelectAllPersonStmt);
    if (result!=0) err_exit("execute select all failed");

    row = 0;
    while(1){
        row++;
        result = mysql_stmt_fetch(gSelectAllPersonStmt);
        if (result == MYSQL_NO_DATA){
            printf("there is not data any more\n");
            break;
        }
        if (result != 0){
            printf("error happened while fetch data error code is:%d\n", result);
            printf("error str is %s \n", mysql_error(gDbConn));
            break;
        }

        strName[lenName]='\0';
        strOpaque[lenOpaque]='\0';
        printf("row %d: id=%d name=%s opaque=%s\n", row, longResult, strName, strOpaque);
    }

    mysql_free_result(metaData);
}

void closePreparedStatements(){
    mysql_stmt_close(gInsertPersonStmt);
    mysql_stmt_close(gDeleteAllPersonStmt);
    mysql_stmt_close(gDeleteAPersonStmt);
    mysql_stmt_close(gSelectAllPersonStmt);
}

void closeDb(MYSQL* dbconn){
    mysql_close(dbconn);
}

int main() {
    int result;
    printf("testing mariadb API\n");

    gDbConn = initDb();
    initPreparedStatements(gDbConn);

    deleteAllPerson();
    /* insert persons */
    insertPerson(1,"name 1", "opaque 1");
    insertPerson(2,"name 2", "opaque 2");
    insertPerson(3,"name 3", "opaque 3");
    insertPerson(4,"name 4", "opaque 4");
    deleteAPerson(4);
    selectAllPerson();

    closePreparedStatements();
    closeDb(gDbConn);

    return 0;
}

void err_exit(char* s){
    perror(s);
    perror("\n");
    exit(1);
}
