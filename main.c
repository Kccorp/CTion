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
        /*for (i = 0; i < 3; ++i) {
            if (i > 0)printf("\nIdentifiants incorrect \nVeuillez réessayer");
            //entrer pseudo
            ask_pseudo(pseudo);

            //entrer password
            ask_password(pwd);

            //Récupere les utilisateurs
            showUser (conn, pseudo, checkPwd);

            //Vérifie si l'utilisateur à rentrée le bon mot de passe
            check_password(pwd, checkPwd, connected);
            //sort de la boucle si bon identifiants
            if (*connected == 1)break;
            if (i == 2){
                printf("\nConnexion interrompu - arret du programme");
                exit(1);
            }
        }*/

        do {
            windowConnect(argc, argv, pwd, pseudo);
            showUser (conn, pseudo, checkPwd);
            check_password(pwd, checkPwd, connected);
            if(*connected==0)tmpGtkError=2;
        } while (*connected == 0);

        printf("connected : %d", *connected);



    } else if (choice == 2) {//Choisir de S'inscrire
        int uniqueName=0;

        //demande à l'utilisateur ses infos de comtpes et vérifie si un pseudo identique existe déjà
        /*do {
            register_pseudo(pseudo, &uniqueName);
            register_password(pwd);
            verifUser(conn,pseudo, &uniqueName);
        } while (uniqueName != 1);*/

        do {
            windowConnect(argc, argv, pwd, pseudo);
            remove_n(pseudo, 25);
            verifUser(conn,pseudo, &uniqueName);
            if(uniqueName!=0)tmpGtkError=1;
        } while (pseudo[0]=='\0' || uniqueName !=1);


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

    int state = 0;
    char pseudo [25]={0};

    MYSQL *conn= mysql_init(NULL);/*Create database link pointer*/

    connectBD(&state, conn);


    if (state == 1) {

        int id_user;
        int connected = 0;

        //prepare les requetes
        initPrepareSql(conn);

        connectUser(&connected, conn,  argc,  argv, pseudo);


        if (connected == 1){
            printf("\n\n\ninsertion\n");
            char titre[20]= "Titre 2";
            char content[15000]= "ezgzerv";
            char description[20]= "ezgzerv";

            fgets(titre, 20, stdin);

            insertDoc(titre, content, description);

        }
    /*        int choice;
            while (choice > 3 || choice <= 0 ){
                printf("\nBonjour %s", pseudo\n)
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
                printf("Saisir un titre : ");
                fgets(titre, 150, stdin);
                printf("Saisir une description : ");
                fgets(description, 300, stdin);
                printf("Vous pouvez saisir votre contenu : \n");
                fgets(content, 20000, stdin); //probleme avec le fgets prend un max de 4096

                //parse(content);

                printf("la phrase %s", content);

                //insertDoc(titre, content, description);

              initPrepareSql(conn);
                char test[20]= "main";
                char test1[15000]= "ezgzerv";
                char test2[20]= "ezgzerv";
                insertDoc(test, test1, test2);

            }
            else if (choice == 3){
                printf("Goodbye !");
                exit(0);
            }
        }
    */
       // closePreparedStatements();
       // closeDb(conn);

    } else {
        return 1;
    }
}


