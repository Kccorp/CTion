#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "mysql.c"
#include "editor.c"
#include "account.c"
#include "graphique.c"
#include "fileConfig.c"

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

void askDoc (char *titre, char *content, char *description){
    printf("Saisir un titre : ");
    fgets(titre, 150, stdin);
    printf("Saisir une description : ");
    fgets(description, 300, stdin);
    printf("Vous pouvez saisir votre contenu : \n");
    fgets(content, 15000, stdin); //probleme avec le fgets prend un max de 4096
}

void verifContent(char *titre, char * content, char *description){
    if (strlen(content)>14990){
        char reload[5];
        printf("\nVotre contenu fait la taille maximum une partie a pu être supprimé voulez-vous resaisir votre contenu? (y/n)");
        fgets(reload, 5, stdin);
        remove_n(reload, 5);
        if (strcmp(reload,"y")==0 || strcmp(reload,"Y")==0 || strcmp(reload,"yes")==0 || strcmp(reload,"YES")==0 ){
            askDoc(titre, content, description);
            verifContent(titre, content, description);
        }
    }
}

void connectUser (int *connected, MYSQL *conn, int argc, char **argv, char *pseudo, char *window_size_x, char *window_size_y){
    int choice;
    char pwd[100];
    char checkPwd[100]={0};
    int i=0;

    //choix entre connexion/inscription
    main_menu(&choice);

    if (choice == 1){//Choisir de se connecter

        do {
            windowConnect(argc, argv, pwd, pseudo, window_size_x, window_size_y);
            showUser (conn, pseudo, checkPwd);
            check_password(pwd, checkPwd, connected);
            if(*connected==0)tmpGtkError=2;
        } while (*connected == 0);

    } else if (choice == 2) {//Choisir de S'inscrire
        int uniqueName=0;

        //demande à l'utilisateur ses infos de comtpes et vérifie si un pseudo identique existe déjà
        do {
            windowConnect(argc, argv, pwd, pseudo, window_size_x, window_size_y);
            remove_n(pseudo, 25);
            verifUser(conn,pseudo, &uniqueName);
            if(uniqueName!=0)tmpGtkError=1;
        } while (pseudo[0]=='\0' || uniqueName !=1);


        //fait l'injection dans la db
        insertUser(pseudo, pwd);
        *connected = 1;
        printf("\nInscription validée - vous êtes connecté\n");

    } else if (choice == 3) {
        printf("\nGoodbye");
        exit(0);
    }
}

int main(int argc, char **argv) {

    int state = 0;
    char pseudo [25]={0};
    char window_size_x[10], window_size_y[10], hostDB[100], nameDB[50];

    fileConfig(window_size_x, window_size_y, hostDB, nameDB); //recupere les donnée du fichier de conf

    MYSQL *conn= mysql_init(NULL);/*Create database link pointer*/

    connectBD(&state, conn, hostDB, nameDB);


    if (state == 1) {

        int id_user;
        int connected = 0;

        //prepare les requetes
        initPrepareSql(conn);

        connectUser(&connected, conn,  argc,  argv, pseudo, window_size_x, window_size_y);


        if (connected == 1){
            int choice;
            while (choice > 3 || choice <= 0 ){
                printf("\nBonjour %s", pseudo);
                printf("\n\n\n1)Consulter un document.\n2)Créer un document.\n3)Exit.\n");
                scanf("%d", &choice);
                vider_buffer();
            }
            if (choice == 1){
                printf("Work in progress");
            }
            else if (choice == 2){
                //Création du document
                printf("\nTu va créer un document\n");
                char content[15000], titre[150], description[300];

               //if (cpt>0)printf("Le contenu doit être inférieur à 20 000 caracteres");
                /*askDoc(titre, content, description);
                verifContent(titre, content, description); //averti user text trés grand

                parse(content);*/
                //printf("la phrase %s", content);
                strcpy(titre, "titre");
                strcpy(description, "descrip");
                strcpy(content, "super le contennu");
                insertDoc(titre, content, description);

            }
            else if (choice == 3){
                printf("Goodbye !");
                exit(0);
            }
        }

        closePreparedStatements();
        closeDb(conn);

    } else {
        return 1;
    }
}


