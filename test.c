#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "mysql.c"
#include "editor.c"


void err_exit(char* s);

void remove_n(char *chaine, int size){
    int i;
    for ( i = 0; i < size; ++i) {
        if (chaine[i] == '\n'){
            chaine[i] = 0;
        }
    }
}
void parse (char* src){
    int i,j = 0,k = 0;
    int size = strlen(src);
    char result [50][50] = {0};
    char final [150] = {0};

    remove_n(src, 25);
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
        //prepare les requetes
        initPrepareSql(conn);
        char pseudo [25], pwd[100];

        printf("\nle pseudo");
        fgets(pseudo, 50, stdin);

        printf("\nle mdp");
        fgets(pwd, 50, stdin);

        //suppression \n fin de mot
        for ( i = 0; i < 100; ++i) {
            if (i <= 25 && pseudo[i] == '\n'){
                pseudo[i] = 0;
            }
            if (pwd[i] == '\n'){
                pwd[i] = 0;
            }
        }

        insertUser(pseudo, pwd);
    } else {
        return 0;
    }

    /*fgets(phrase, 50, stdin);

    printf("\n%s\n", phrase);
    parse(phrase);*/


}

void err_exit(char* s){
    perror(s);
    perror("\n");
    exit(1);
}
