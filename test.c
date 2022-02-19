#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "mysql.c"

void vider_buffer(void){
    //fflush(stdin);
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);

}

int main(int argc, char **argv) {

    int state = 0, connected=0;

    MYSQL *conn= mysql_init(NULL);/*Create database link pointer*/

    connectBD(&state, conn, "n2o93bb1bwmn0zle.chr7pe7iynqr.eu-west-1.rds.amazonaws.com", "wbz6ulqh7s5afptp");
    initPrepareSql(conn);

    char pseudo[25]="test1";

    char ***result;
    int cpt=0, check=0, i, choice;

    int **taille;

    getDoc (conn, pseudo, result, &cpt, check, taille);

    if (cpt!=0) {
        check = 1;

        taille = malloc(sizeof(int*) * cpt);
        for (i = 0; i < cpt; ++i) {
            taille[i] = malloc(sizeof(int) * cpt);
        }

        //strcpy(result[0][0], "test");

        if (taille != NULL){

            getDoc(conn, pseudo, result, &cpt, check, taille);


            printf("la taille du titre n°1 est %d", taille[1][0]);

            result = malloc(sizeof(char **) * cpt);
            for (i = 0; i < cpt; ++i) {
                result[i] = malloc(sizeof(char*) * 3);
                result[i][0] = malloc(sizeof(char) * taille[i][0]);
                result[i][1] = malloc(sizeof(char) * taille[i][1]);
                result[i][2] = malloc(sizeof(char) * taille[i][2]);
            }

            check=2;
            if (result != NULL){
                getDoc(conn, pseudo, result, &cpt, check, taille);

                do {

                    for (i = 0; i < cpt; i++) {
                        printf("\nDocument %d : %s / %s", i+1, result[i][0], result[i][1]);
                    }
                    printf("\n\nQuel document voulez-vous afficher : ");
                    scanf("%d", &choice);

                    vider_buffer();
                }while(choice>cpt || choice < 1);

                printf("\n\nTitre : %s", result[choice-1][0]);
                printf("\nDescription : %s", result[choice-1][1]);
                printf("\n%s\n\n", result[choice-1][2]);


            }

        } else {
            printf("pas assez de ressources");
            exit(1);
        }
    }



}
