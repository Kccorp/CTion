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

void startConnection(MYSQL *connOld, MYSQL *connNew, int *state, char *hostDB, char *nameDB){
    closePreparedStatements();
    closeDb(connOld);
    connectBD(state, connNew, hostDB, nameDB);
    if (*state == 1)
        initPrepareSql(connNew);
}


int main(int argc, char **argv) {

    int state = 0;
    char pseudo [25]={0};
    char window_size_x[10], window_size_y[10], hostDB[100], nameDB[50];

    fileConfig(window_size_x, window_size_y, hostDB, nameDB); //recupere les donnée du fichier de conf

    MYSQL *conn= mysql_init(NULL);/*Create database link pointer*/

    connectBD(&state, conn, hostDB, nameDB);


    if (state == 1) {

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

                char ***result;
                int **taille;
                int cpt=0, check=0, i;

                MYSQL *conn2= mysql_init(NULL);
                startConnection(conn, conn2, &state, hostDB, nameDB);

                getDoc (conn2, pseudo, result, &cpt, check, taille);

                if (cpt!=0) {
                    check = 1;//variable d'étape

                    //créer le premier tableau qui va stocker la taille de chaque titre, description et contenu de chaque doc de l'utilisateur
                    taille = malloc(sizeof(int*) * cpt);
                    for (i = 0; i < cpt; ++i) {
                        taille[i] = malloc(sizeof(int) * cpt);
                    }

                    if (taille != NULL){

                        getDoc(conn, pseudo, result, &cpt, check, taille); //rappelle la fonction pour remplire le tableau taille

                        //créer les tableaux qui vont stocker les titre, description et contenu de chaque doc de l'utilisateur
                        result = malloc(sizeof(char **) * cpt);
                        for (i = 0; i < cpt; ++i) {
                            result[i] = malloc(sizeof(char*) * 3);
                            result[i][0] = malloc(sizeof(char) * taille[i][0]);
                            result[i][1] = malloc(sizeof(char) * taille[i][1]);
                            result[i][2] = malloc(sizeof(char) * taille[i][2]);
                        }
                        check=2; //variable d'étape

                        if (result != NULL){
                            getDoc(conn, pseudo, result, &cpt, check, taille); //rappelle la fonction pour remplire le tableau result

                            //demande à l'utilisateur quel document afficher
                            do {
                                for (i = 0; i < cpt; i++) {
                                    printf("\nDocument %d : %s / %s", i+1, result[i][0], result[i][1]);
                                }
                                printf("\n\nQuel document voulez-vous afficher : ");
                                scanf("%d", &choice);
                                vider_buffer();
                            }while(choice>cpt || choice < 1);

                            //affiche le document
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
            else if (choice == 2){

                //Création du document
                printf("\nTu va créer un document\n");
                char content[15000], titre[150], description[300];

                askDoc(titre, content, description);
                verifContent(titre, content, description); //averti user text trés grand

                parse(content);

                remove_n(titre, 150);
                remove_n(description, 300);

                MYSQL *conn2= mysql_init(NULL);
                startConnection(conn, conn2, &state, hostDB, nameDB);

                insertDoc(titre, content, description);
                insertAssoc(titre, pseudo);

                printf("le document à été correctement inséré");

            }
            else if (choice == 3){

                printf("Goodbye !");
                exit(0);

            }
        }

    } else {
        return 1;
    }
}


