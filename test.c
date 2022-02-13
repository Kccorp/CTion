#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "mysql.c"
#include "editor.c"
#include "account.c"

void vider_buffer(void){
    //fflush(stdin);
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

void connectUser (int *connected, MYSQL *conn){
    int choice;
    char pseudo [25]={0}, pwd[100];
    char checkPwd[100]={0};
    int i=0;

    //choix entre connexion/inscription
    main_menu(&choice);

    if (choice == 1){//Choisir de se connecter

        //demande à l'utilisateur 3x les identifiants
        for (i = 0; i < 3; ++i) {
            if (i > 0)printf("\nIdentifiants incorrect \nVeuillez réessayer");
            //entrer pseudo
            ask_pseudo(pseudo);

            //entrer password
            ask_password(pwd);

            //Récupere les utilisateurs
            showUser (&*conn, pseudo, checkPwd);

            //Vérifie si l'utilisateur à rentrée le bon mot de passe
            check_password(pwd, checkPwd, connected);
            //sort de la boucle si bon identifiants
            if (*connected == 1)break;
            if (i == 2){
                printf("\nConnexion interrompu - arret du programme");
                exit(1);
            }
        }

    } else if (choice == 2) {//Choisir de S'inscrire
        int uniqueName=0;

        //demande à l'utilisateur ses infos de comtpes et vérifie si un pseudo identique existe déjà
        do {
            register_pseudo(pseudo, &uniqueName);
            register_password(pwd);
            verifUser(conn,pseudo, &uniqueName);
        } while (uniqueName != 1);

        //fait l'injection dans la db
        insertUser(pseudo, pwd);
        *connected = 1;
        printf("Inscription validée - vous êtes connecté");

    } else if (choice == 3) {
        printf("\nGoodbye");
        exit(0);
    }
}


int main(int argc, char **argv) {

    int state = 0, connected=0;

    char pseudo [25]="toto1", pwd[100]="toto1";
    char checkPwd[100]={0};

    MYSQL *conn= mysql_init(NULL);/*Create database link pointer*/


    connectBD(&state, conn);
    initPrepareSql(conn);

    //connectUser(&connected, conn);


    //Récupere les utilisateurs
    showUser (&*conn, pseudo, checkPwd);

    insertUser(pseudo, pwd );

    //check_password(pwd, checkPwd, &connected);



    /*if (state == 1) {
        char titre[20]= "Titre 2";
        char content[15000]= "ezgzerv";
        char description[20]= "ezgzerv";

        fgets(titre, 20, stdin);

        insertDoc(titre, content, description);
        return 0;
    }*/
   /* int state = 0;


    char phrase [20000] ;

    vider_buffer();

    fgets(phrase, 20000-1, stdin);*/

    /*int max, cpt=0, cptWord=1, i;
    for (i = 0; i < strlen(phrase); ++i) { //size-1 pour ne pas prendre en compte \0 du fgets
        if (phrase[i] != 32 ){
            cpt++;

        }else{
            if (cpt > max)max=cpt;
            cpt=0;
            cptWord++;
        }
    }

    printf("\nmaxlength : %d", max);
    printf("\nnbr mots : %d", cptWord);
*/
   //parse(phrase);
}
