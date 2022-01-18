#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define INSERT_USER "INSERT INTO cTion.user (pseudo, pwd) VALUES (?,  ?)"

void err_exit(char* s);

MYSQL_STMT* addUser = NULL;

void connectBD (int *state, MYSQL *conn){

    if(conn == NULL) { /*If it returns NULL, the initialization failed*/
        printf("mysql_init failed!\n");
    }
    conn=mysql_real_connect(conn,"192.168.50.133","cTion_user","1234","cTion",3306,NULL,0);
    if (conn) {
        printf("Connection success!\n");
        *state = 1;
    }else{
        printf("Connection failed!\n");
        *state = 0;
    }
}

void initPrepareSql (MYSQL *conn){
    int prepare;
    unsigned long count;

    addUser = mysql_stmt_init(conn);
    if (addUser == NULL) err_exit("init stmt failed");
    prepare = mysql_stmt_prepare(addUser, INSERT_USER, strlen(INSERT_USER));
    if (prepare != 0) err_exit("prepare stmt failed");
    count = mysql_stmt_param_count(addUser);
    printf("Il y a %ld parametre dans l'sql preparé\n", count);

}

void insertUser(char* pseudo, char* pwd ){
    MYSQL_BIND bind[2]; // il y a deux places pseudo et mdp

    unsigned int array_size = 1; /* the number of row to insert? */
    unsigned long pseudoLen = strlen(pseudo);
    unsigned long pwdLen = strlen(pwd);
    int result;

    memset(bind, 0, sizeof(MYSQL_BIND)*2);

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = pseudo;
    bind[0].buffer_length = strlen(pseudo);
    bind[0].length = &pseudoLen;

    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = pwd;
    bind[1].buffer_length = strlen(pwd);
    bind[1].length = &pwdLen;

    mysql_stmt_attr_set(addUser, STMT_ATTR_ARRAY_SIZE, &array_size);
    result = mysql_stmt_bind_param(gInsertPersonStmt, bind);
    if (result != 0) err_exit("bind stmt insert failed");
    result = mysql_stmt_execute(gInsertPersonStmt);
    if (result != 0) err_exit("execute stmt insert failed");
}

char redColor (char* src){
    //printf("\n%s", src);
    char red [50]="\033[0;31m";
    strncpy(src, red, 10);
    //printf("\n%s", src);
}

char blueColor (char* src){
    //printf("\n%s", src);
    char red [50]="\033[0;34m";
    strncpy(src, red, 10);
    //printf("\n%s", src);
}

char reset (char* src){
    char red [50]="\033[0m";
    strncpy(src, red, 7);
}

char parse (char* src){
    int i,j = 0,k = 0;
    int size = strlen(src);
    char result [50][50] = {0};
    char final [150] = {0};


    /*for (int i = 0; i < 50; ++i) {
        for (int j = 0; j < 50; ++j) {
            result[i][j] = 0;
        }
    }*/

    //sépare les mots
    for (i = 0; i < size; ++i) {
        if (src[i] != 32){
            result[j][k] = src[i];
            k++;
        } else{
            ++j;
            k = 0;
        }
    }

    result[j][k] = '\0';

    //Détection de couleur
    int color = 0;
    for (i = 0; i < 50; ++i) {
        if (strcmp(result[i], "red[") == 0 && color == 0){
            redColor(result[i]);
            color = 1;
        } else if (strcmp(result[i], "blue[") == 0 && color == 0){
            blueColor(result[i]);
            color = 1;
        } else if (strcmp(result[i], "]") == 0 && color == 1){
            reset(result[i]);
            color = 0;
        }
    }


    //Affichage du tableau 2D
    for ( i = 0; i < 50; ++i) {
        if (result[i][0] != 0){
            printf("%s", result[i]);
            printf("\n");
        }
    }

    printf("-------------------");

    int last;
    for ( i = 0; i < 50; ++i) {
        if (result[i][0] != 0){
             strcat(final,result[i]);
            last = strlen(final);
            final[last] = 32;
        }
    }

    printf("\n la phrase est : %s", final);

}


int main(int argc, char **argv) {

    char phrase [50];// "Je blue[ suis ] un red[ text  cool ] super" ;
    int size, i,j;

    int state = 0;
    MYSQL *conn= mysql_init(NULL);/*Create database link pointer*/

    connectBD(&state, conn);

    if (state == 1) {
        initPrepareSql(conn);
    }

    /*fgets(phrase, 50, stdin);

    printf("\n%s\n", phrase);
    parse(phrase);*/

 return 0;
}

void err_exit(char* s){
    perror(s);
    perror("\n");
    exit(1);
}
