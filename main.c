#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "mysql.c"
#include "editor.c"
#include "account.c"
#include "graphique.c"

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

void connectUser (int *connected, MYSQL *conn, int argc, char **argv, char *pseudo){
    int choice;
    char pwd[100];
    char checkPwd[100]={0};
    int i=0;

    //choix entre connexion/inscription
    main_menu(&choice);

    if (choice == 1){//Choisir de se connecter

        //demande à l'utilisateur 3x les identifiants
        do {
            windowConnect(argc, argv, pwd, pseudo);
            showUser (conn, pseudo, checkPwd);
            check_password(pwd, checkPwd, connected);
            if(*connected==0)tmpGtkError=2;
        } while (*connected == 0);



    } else if (choice == 2) {//Choisir de S'inscrire
        int uniqueName=0;

        //demande à l'utilisateur ses infos de comtpes et vérifie si un pseudo identique existe déjà
        do {
            windowConnect(argc, argv, pwd, pseudo);
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

void askContent (char *titre, char *description, char *content){
    //Demande les infos du document
    printf("\nTu va créer un document\n");
    printf("Saisir un titre : ");
    fgets(titre, 150, stdin);
    remove_n(titre, 150);
    printf("Saisir une description : ");
    fgets(description, 300, stdin);
    remove_n(description, 300);
    printf("Vous pouvez saisir votre contenu : \n");
    fgets(content, 15000, stdin); //probleme avec le fgets prend un max de 4096
    remove_n(content, 15000);
}

void errorContent (char *tmp, char *titre, char *description, char *content){
    if(strlen(content) >= 14999){
        printf("\n\033[0;31mATTENTION\033[0m : votre text fait le maximum de caractéres une partie à pu être supprimé");
        printf("\nVoulez vous resaisir votre document  ? y/n\n");
        fgets(tmp, 2, stdin);


        if (strcmp(tmp,"y")==0 || strcmp(tmp,"Y")==0){
            askContent(titre, description, content);
            errorContent(tmp, titre, description, content);
        }
    }
}

int main(int argc, char **argv) {

    int state = 0;

    MYSQL *conn= mysql_init(NULL);/*Create database link pointer*/
    connectBD(&state, conn);

    if (state == 1) {   //si la connexion à la bd est OK
        int id_user; //pas sur de garder cette variable
        int connected = 0;
        char pseudo [25]={0};
        int choice = 0;

        //prepare les requetes
        initPrepareSql(conn);

        //Connecte ou inscrit l'utilisateur
        //connectUser(&connected, conn,  argc,  argv, pseudo);


        connected = 1;
        strcpy(pseudo, "test");
        if (connected == 1){
            char content[15000], titre[150], description[300];
            char tmp[10];

            while (choice > 3 || choice <= 0 ){
                printf("\n\nBonjour %s", pseudo);
                printf("\n\n1)Consulter un document.\n2)Créer un document.\n3)Exit.\n");
                scanf("%d", &choice);
                vider_buffer();
            }

            if (choice == 1){  //Afficher les documents de l'utilisateur

                printf("Work in progress");

            } else if (choice == 2) {  //Insérer un document

                //demande le titre, la description et le contenu à l'utilisateur
                askContent(titre,description, content);

                //demande vérification à l'utilisateur
                errorContent(tmp, titre,description, content);

                //transforme le contenu
                parse(content);
                printf("\nla phrase %s", content);

                //Insérer le document en base de donnée
                insertDoc(titre, content, description);
            }

            //Quite la session
            else if (choice == 3){
                printf("Goodbye !");
                exit(0);
            }

            closePreparedStatements();
            closeDb(conn);
        }

    } else {
        return 1;
    }
}


