//
// Created by Keissy on 19/01/2022.
//

#define INSERT_USER "INSERT INTO user (pseudo, pwd) VALUES (?,  ?)"
#define INSERT_DOC "INSERT INTO document (titre, contenu, description) VALUES (?,  ?, ?)"
#define INSERT_ASSOC "INSERT INTO possede (pseudo, titreDoc) VALUES (?, ?)"
#define SELECT_USER "SELECT pseudo, pwd from user"
#define CHECK_USER "SELECT pseudo from user"
#define GET_DOC "SELECT titre, contenu, description from document inner join possede on document.titre = possede.titreDoc inner join user on possede.pseudo = user.pseudo where user.pseudo = ?"
#define UPDATE_DOC "UPDATE document set contenu = ? where titre = ?"

MYSQL_STMT* addUser = NULL;
MYSQL_STMT* selectUser = NULL;
MYSQL_STMT* checkUser = NULL;
MYSQL_STMT* addDoc = NULL;
MYSQL_STMT* addAssoc = NULL;
MYSQL_STMT* selectDoc = NULL;
MYSQL_STMT* updateDoc = NULL;

void err_exit(char* s);

void connectBD (int *state, MYSQL *conn, char *hostDB, char *bnName){

    if(conn == NULL) { /*If it returns NULL, the initialization failed*/
        printf("mysql_init failed!\n");
    }
    //conn=mysql_real_connect(conn,"192.168.50.133","cTion_user","1234","cTion",3306,NULL,0);
    conn=mysql_real_connect(conn,"n2o93bb1bwmn0zle.chr7pe7iynqr.eu-west-1.rds.amazonaws.com","pz51cw591tewd1lp","n78bgxgqf4u510mu",bnName,3306,NULL,0);
    if (conn) {
        printf("\033[0;34mConnection success! \033[0m\n");
        *state = 1;
    }else{
        printf("\033[0;31mConnection failed! \033[0m\n");
        *state = 0;
    }
}

void initPrepareSql (MYSQL *conn){
    int prepare;
    unsigned int count;

    addUser = mysql_stmt_init(conn);
    if (addUser == NULL) err_exit("init stmt failed");
    prepare = mysql_stmt_prepare(addUser, INSERT_USER, strlen(INSERT_USER));
    if (prepare != 0) err_exit("prepare stmt failed");
    count = mysql_stmt_param_count(addUser);
    printf("Il y a %d parametre dans l'sql preparé Insert User\n", count);

    selectUser = mysql_stmt_init(conn);
    if (selectUser == NULL) err_exit("init stmt failed");
    prepare = mysql_stmt_prepare(selectUser, SELECT_USER, strlen(SELECT_USER));
    if (prepare != 0) err_exit("prepare stmt failed");

    checkUser = mysql_stmt_init(conn);
    if (checkUser == NULL) err_exit("init stmt failed");
    prepare = mysql_stmt_prepare(checkUser, CHECK_USER, strlen(CHECK_USER));
    if (prepare != 0) err_exit("prepare stmt failed");

    addDoc = mysql_stmt_init(conn);
    if (addDoc == NULL) err_exit("init stmt failed");
    prepare = mysql_stmt_prepare(addDoc, INSERT_DOC, strlen(INSERT_DOC));
    if (prepare != 0) err_exit("prepare stmt failed");
    count = mysql_stmt_param_count(addDoc);
    printf("Il y a %d parametre dans l'sql preparé Insert Document\n", count);

    addAssoc = mysql_stmt_init(conn);
    if (addAssoc == NULL) err_exit("init stmt failed");
    prepare = mysql_stmt_prepare(addAssoc, INSERT_ASSOC, strlen(INSERT_ASSOC));
    if (prepare != 0) err_exit("prepare stmt failed");
    count = mysql_stmt_param_count(addAssoc);
    printf("Il y a %d parametre dans l'sql preparé Insert Assoc\n", count);

    selectDoc = mysql_stmt_init(conn);
    if (selectDoc == NULL) err_exit("init stmt failed");
    prepare = mysql_stmt_prepare(selectDoc, GET_DOC, strlen(GET_DOC));
    if (prepare != 0) err_exit("prepare stmt failed");
    count = mysql_stmt_param_count(selectDoc);
    printf("Il y a %d parametre dans l'sql preparé getDoc\n", count);

    updateDoc = mysql_stmt_init(conn);
    if (updateDoc == NULL) err_exit("init stmt failed");
    prepare = mysql_stmt_prepare(updateDoc, UPDATE_DOC, strlen(UPDATE_DOC));
    if (prepare != 0) err_exit("prepare stmt failed");
    count = mysql_stmt_param_count(updateDoc);
    printf("Il y a %d parametre dans l'sql preparé updateDoc\n", count);

}

void insertAssoc(char *titre, char *pseudo){
    MYSQL_BIND bind[2];

    unsigned int array_size = 1; // the number of row to insert?
    unsigned long titreLen = strlen(titre);
    unsigned long pseudoLen = strlen(pseudo);
    int result;

    memset(bind, 0, sizeof(MYSQL_BIND)*2);

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = pseudo;
    bind[0].buffer_length = strlen(pseudo);
    bind[0].length = &pseudoLen;

    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = titre;
    bind[1].buffer_length = strlen(titre);
    bind[1].length = &titreLen;

    mysql_stmt_attr_set(addAssoc, 2, &array_size);
    result = mysql_stmt_bind_param(addAssoc, bind);
    if (result != 0) err_exit("bind stmt insert failed");
    result = mysql_stmt_execute(addAssoc);
    if (result != 0) err_exit("execute stmt insert failed");
}

void UpdateDocument(char *content){
    MYSQL_BIND bind[2];

    char titre[15]="Top steam";
    unsigned int array_size = 1; // the number of row to insert?
    unsigned long titreLen = strlen(titre);
    unsigned long contentLen = strlen(content);
    int result;

    memset(bind, 0, sizeof(MYSQL_BIND)*2);

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = content;
    bind[0].buffer_length = strlen(content);
    bind[0].length = &contentLen;

    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = titre;
    bind[1].buffer_length = strlen(titre);
    bind[1].length = &titreLen;

    mysql_stmt_attr_set(updateDoc, 2, &array_size);
    result = mysql_stmt_bind_param(updateDoc, bind);
    if (result != 0) err_exit("bind stmt insert failed");
    result = mysql_stmt_execute(updateDoc);
    if (result != 0) err_exit("execute stmt insert failed");
}

void insertDoc(char *titre, char *content , char* description ){
    MYSQL_BIND bind[3];

    unsigned int array_size = 1; /* the number of row to insert? */
    unsigned long titreLen = strlen(titre);
    unsigned long contentLen = strlen(content);
    unsigned long descriptionLen = strlen(description);
    int result;

    memset(bind, 0, sizeof(MYSQL_BIND)*3);

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = titre;
    bind[0].buffer_length = strlen(titre);
    bind[0].length = &titreLen;

    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = content;
    bind[1].buffer_length = strlen(content);
    bind[1].length = &contentLen;

    bind[2].buffer_type = MYSQL_TYPE_STRING;
    bind[2].buffer = description;
    bind[2].buffer_length = strlen(description);
    bind[2].length = &descriptionLen;

    mysql_stmt_attr_set(addDoc, 3, &array_size);
    result = mysql_stmt_bind_param(addDoc, bind);
    if (result != 0) err_exit("bind stmt insert failed");
    result = mysql_stmt_execute(addDoc);
    if (result != 0) err_exit("execute stmt insert failed");
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

    mysql_stmt_attr_set(addUser, 2, &array_size);
    result = mysql_stmt_bind_param(addUser, bind);
    if (result != 0) err_exit("bind stmt insert failed");
    result = mysql_stmt_execute(addUser);
    if (result != 0) err_exit("execute stmt insert failed");
}

void showUser (MYSQL *conn, char *pseudoSaisie, char *password){

    char strPseudo[25];
    char strpwd[150];
    unsigned long lenName;
    unsigned long lenpwd;
    int result;
    int row;
    MYSQL_BIND bind[2]; /*used to get result, not to provide parameters*/
    MYSQL_FIELD *fields;
    MYSQL_RES *metaData;

    metaData = mysql_stmt_result_metadata(selectUser);
    if (metaData == NULL) err_exit("impossible d'obtenir les metadonnées");

    fields = mysql_fetch_fields(metaData);
    memset(bind,0,sizeof(MYSQL_BIND)*2);

    bind[0].buffer_type = fields[0].type;
    bind[0].buffer = strPseudo;
    bind[0].buffer_length = 25;
    bind[0].length = &lenName;

    bind[1].buffer_type = fields[1].type;
    bind[1].buffer = strpwd;
    bind[1].buffer_length = 100;
    bind[1].length = &lenpwd;


    result = mysql_stmt_bind_result(selectUser, bind);
    if (result!=0) err_exit("Le stockage des données à échoué");

    result = mysql_stmt_execute(selectUser);
    if (result!=0) err_exit("l'éxecution du select à échoué");

    row = 0;
    while(1){
        row++;
        result = mysql_stmt_fetch(selectUser);
        if (result == MYSQL_NO_DATA){
            //printf("-- FIN --\n");
            break;
        }
        if (result != 0){
            printf("Il y a eu une erreur code:%d\n", result);
            printf("error str is %s \n", mysql_error(conn));
            break;
        }

        strPseudo[lenName]='\0';
        strpwd[lenpwd]='\0';
        //printf("ligne %d: id=%d pseudo=%s password=%s\n", row, id, strPseudo, strpwd);

        if (strcmp(pseudoSaisie, strPseudo) == 0){
            //printf("\nUn compte existe");
            strcpy(password, strpwd);
            break;
        }

    }

    mysql_free_result(metaData);
    if (metaData==NULL)
        printf("metaData clear");
}

void verifUser (MYSQL *conn, char *pseudoSaisie, int *verif){
    char strPseudo[25];
    unsigned long lenName;
    int result;
    int row;
    MYSQL_BIND bind[1]; /*used to get result, not to provide parameters*/
    MYSQL_FIELD *fields;
    MYSQL_RES *metaData;
    //my_bool isNull[1];


    metaData = mysql_stmt_result_metadata(checkUser);
    if (metaData == NULL) err_exit("impossible d'obtenir les metadonnées");

    fields = mysql_fetch_fields(metaData);
    memset(bind,0,sizeof(MYSQL_BIND));

    bind[0].buffer_type = fields[0].type;
    bind[0].buffer = strPseudo;
    bind[0].buffer_length = 25;
    //bind[0].is_null = &isNull[0];
    bind[0].length = &lenName;


    result = mysql_stmt_bind_result(checkUser, bind);
    if (result!=0) err_exit("Le stockage des données à échoué");

    result = mysql_stmt_execute(checkUser);
    if (result!=0) err_exit("l'éxecution du select à échoué");

    row = 0;
    while(1){

        result = mysql_stmt_fetch(checkUser);


        if (result != 0 && row == 0){
            printf("Il y a eu une erreur code:%d\n", result);
            printf("error str is %s \n", mysql_error(conn));
            break;
        }

        strPseudo[lenName]='\0';
        //printf("ligne %d: pseudo=%s Pseudo Saisi=%s \n", row, strPseudo, pseudoSaisie);

        if (strcmp(pseudoSaisie, strPseudo) == 0){
            *verif = 2;
            break;
        }

        if (result != 0 && row != 0){
            *verif = 1;
            break;
        }
        row++;

    }

    mysql_free_result(metaData);
}

void getDoc (MYSQL *conn, char *pseudo, char ***docs, int *cpt, int check, int **taille){
    char strTitre[150];
    char strDescription[300];
    char strContent[15000];
    unsigned long lenTitre;
    unsigned long lenDescriptionn;
    unsigned long lenContent;
    unsigned long pseudoLen = strlen(pseudo);
    int result, result1;
    int row;
    unsigned int array_size = 1;
    MYSQL_BIND bind[3]; /*used to get result, not to provide parameters*/
    MYSQL_BIND insertBind[1];
    MYSQL_FIELD *fields;
    MYSQL_RES *metaData;
    //my_bool isNull[1];


    metaData = mysql_stmt_result_metadata(selectDoc);
    if (metaData == NULL) err_exit("impossible d'obtenir les metadonnées");

    fields = mysql_fetch_fields(metaData);
    memset(bind,0,sizeof(MYSQL_BIND)*3); //reserve la mémoire pour le l'obtention des resultats
    memset(insertBind,0,sizeof(MYSQL_BIND)); //reserve la mémoire pour définir le paramètre

    insertBind[0].buffer_type = MYSQL_TYPE_STRING;
    insertBind[0].buffer = pseudo;
    insertBind[0].buffer_length = strlen(pseudo);
    insertBind[0].length = &pseudoLen;

    bind[0].buffer_type = fields[0].type;
    bind[0].buffer = strTitre;
    bind[0].buffer_length = 150;
    //bind[0].is_null = &isNull[0];
    bind[0].length = &lenTitre;

    bind[1].buffer_type = fields[1].type;
    bind[1].buffer = strContent;
    bind[1].buffer_length = 15000;
    //bind[0].is_null = &isNull[0];
    bind[1].length = &lenContent;

    bind[2].buffer_type = fields[2].type;
    bind[2].buffer = strDescription;
    bind[2].buffer_length = 300;
    //bind[0].is_null = &isNull[0];
    bind[2].length = &lenDescriptionn;

    mysql_stmt_attr_set(selectDoc, 1, &array_size);
    result1 = mysql_stmt_bind_param(selectDoc, insertBind);
    if (result1 != 0) err_exit("bind stmt insert failed");
    result1 = mysql_stmt_execute(selectDoc);
    if (result1 != 0) err_exit("execute stmt insert failed");

    result = mysql_stmt_bind_result(selectDoc, bind);
    if (result!=0) err_exit("Le stockage des données à échoué");

    result = mysql_stmt_execute(selectDoc);
    if (result!=0) err_exit("l'éxecution du select à échoué");

    row = 0;
    while(1){

        result = mysql_stmt_fetch(selectDoc);


        if (result != 0 && row == 0){
            printf("Il y a eu une erreur code:%d\n", result);
            printf("error str is %s \n", mysql_error(conn));
            break;
        }

        if (result == MYSQL_NO_DATA ){
            if (check == 0)
                printf("-- FIN --\n");
            break;
        }

        strTitre[lenTitre]='\0';
        strDescription[lenDescriptionn]='\0';
        strContent[lenContent]='\0';

        if (check == 0) {
            //printf("ligne %d: titre=%s Description=%s lencontenu=%s \n", row, strTitre, strDescription, strContent);
            *cpt = *cpt + 1;
        }

        if (check == 1) {
            taille[row][0] = lenTitre;
            taille[row][1] = lenDescriptionn;
            taille[row][2] = lenContent;
        }

        if (check == 2){
            strcpy(docs[row][0], strTitre);
            strcpy(docs[row][1], strDescription);
            strcpy(docs[row][2], strContent);
        }

        row++;

    }

    mysql_free_result(metaData);
}



void closePreparedStatements(){
    mysql_stmt_close(addUser);
    mysql_stmt_close(selectUser);
    mysql_stmt_close(checkUser);
    mysql_stmt_close(addDoc);
    mysql_stmt_close(addAssoc);
    mysql_stmt_close(selectDoc);
    mysql_stmt_close(updateDoc);

}

void closeDb(MYSQL* dbconn){
    mysql_close(dbconn);
}

void err_exit(char* s){
    perror(s);
    perror("\n");
    exit(1);
}