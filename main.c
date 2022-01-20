#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "mysql.c"
#include "editor.c"

void vider_buffer(void){
    int c;

    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

void remove_n(char *chaine, int size){
    int i;
    for ( i = 0; i < size; ++i) {
        if (chaine[i] == '\n'){
            chaine[i] = 0;
        }
    }
}

int main(int argc, char **argv) {

    char phrase [50];// "Je blue[ suis ] un red[ text  cool ] super" ;
    int size, i,j;

    int state = 0;

    MYSQL *conn= mysql_init(NULL);/*Create database link pointer*/

    connectBD(&state, conn);

    if (state == 1) {
        char pseudo [25]={0}, pwd[100];
        char checkPwd[100]={0};
        int choice;
        short connected = 0;

        if (connected == 0){
            while (choice > 3 || choice <= 0 ){
                printf("\n1)Se connecter\n2)S'inscrire\n3)Exit\n");
                scanf("%d", &choice);
                vider_buffer();
            }
            if (choice == 1){//Choisir de se connecter
                //entrer pseudo
                do {
                    printf("\nSe connecter\nPseudo : ");
                    fgets(pseudo, 25, stdin);
                    remove_n(pseudo, 25);
                } while (pseudo[0] == 0);

                //entrer password
                do {
                    printf("\nSe connecter\nMot de passe : ");
                    fgets(pwd, 100, stdin);
                    remove_n(pwd, 100);
                } while (pwd[0] == 0);



            } else if (choice == 2) {
                //Choisir de S'inscrire
                printf("le choix 2");
            } else if (choice == 3) {
                printf("\nGoodbye");
                return 0;
            }
        }
        /*
        //prepare les requetes


        //############################
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
        //#############################

        //insertUser(pseudo, pwd);
        showUser (conn, pseudo, checkPwd);

        //Vérifie si l'utilisateur à rentrée le bon mot de passe
        if (checkPwd[0] != 0){
            printf("\nle mot de passe de %s est %s", pseudo, checkPwd);
            if (strcmp(pwd, checkPwd) == 0){
                printf("\nle mdp est correct connexion validé");
            } else {
                printf("\nle mdp est incorrect connexion refusé");
            }
        }*/

    } else {
        return 0;
    }

    /*fgets(phrase, 50, stdin);

    printf("\n%s\n", phrase);
    parse(phrase);*/


}


