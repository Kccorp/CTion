//
// Created by Keissy on 19/01/2022.
//

void redColor (char* src){
    char red [10]="\033[0;31m";
    strncpy(src, red, 10);
}

void boldRedColor (char* src){
    char bred [10]="\033[1;31m";
    strncpy(src, bred, 10);
}

void blueColor (char* src){
    char blue [10]="\033[0;34m";
    strncpy(src, blue, 10);
}

void boldBlueColor (char* src){
    char bblue [10]="\033[1;34m";
    strncpy(src, bblue, 10);
}

void purpleColor (char* src){
    char purple [10]="\033[0;35m";
    strncpy(src, purple, 10);
}

void boldPurpleColor (char* src){
    char bpurple [10]="\033[1;35m";
    strncpy(src, bpurple, 10);
}

void bold (char* src){
    char bold [10]="\033[1m";
    strncpy(src, bold, 7);
}

void reset (char* src){
    char reset [10]="\033[0m";
    strncpy(src, reset, 7);
}

void analyse(char **result, int color, unsigned int cptWord){
    //Analyse des mots
    int i;
    for (i = 0; i < cptWord; ++i) {
        if (strcmp(result[i], "red[") == 0 && color == 0){
            redColor(result[i]);
            color = 1;
        } else if (strcmp(result[i], "blue[") == 0 && color == 0){
            blueColor(result[i]);
            color = 1;
        } else if (strcmp(result[i], "purple[") == 0 && color == 0){
            purpleColor(result[i]);
            color = 1;
        } else if (strcmp(result[i], "Bred[") == 0 && color == 0){
            boldRedColor(result[i]);
            color = 1;
        } else if (strcmp(result[i], "Bblue[") == 0 && color == 0){
            boldBlueColor(result[i]);
            color = 1;
        } else if (strcmp(result[i], "Bpurple[") == 0 && color == 0){
            boldPurpleColor(result[i]);
            color = 1;
        } else if (strcmp(result[i], "bold[") == 0 && color == 0){
            bold(result[i]);
            color = 1;
        } else if (strcmp(result[i], "]") == 0  && color == 1){
            reset(result[i]);
            color = 0;
        }
    }
}

void split(unsigned int size, char *src, char **result){
    //sépare les mots
    unsigned int i, j=0, k=0;
    for (i = 0; i < size-1; ++i) { //size-1 pour ne pas prendre en compte \0 du fgets
        if (src[i] != 32 ){
            result[j][k] = src[i];
            k++;
        } else{
            ++j;
            k = 0;
        }
    }
    result[j][k] = '\0';
}

void parse (char* src){
    unsigned long long int i;
    unsigned int size = strlen(src);
    //printf("la size : %llu", size);
    //char result [10050][20000] = {0};
    char final [15000] = {0};


    int max, cpt=0;
    unsigned int cptWord=1;
    for (i = 0; i < size; ++i) { //size-1 pour ne pas prendre en compte \0 du fgets
        if (src[i] != 32 ){
            if (cpt > max)max=cpt;
            cpt++;
        }else{
            cpt=0;
            cptWord++;
        }
    }

    if (max < 10)max=10;

    //printf("\nnbr mots : %d", cptWord);
    //printf("\nmaxlength : %d", max);


    cptWord++;
    max++;
    char **result = malloc(cptWord * sizeof(char*));
    for (i = 0; i < cptWord; ++i) {
        result[i] = malloc(max * sizeof(char));
    }

    for ( i = 0; i < cptWord; ++i) {
        for (int j = 0; j < max; ++j) {
            result[i][j] = 0;
        }
    }


    if (result != NULL){

        split(size, src, result);

        int color = 0;
        analyse(result, color, cptWord);

        //Affichage du tableau 2D
        for ( i = 0; i < cptWord; ++i) {
            if (result[i][0] != 0){
                printf("\n%s", result[i]);
            }
        }

        //reconstitution de la phrase
        int last;
        for ( i = 0; i < cptWord; ++i) {
            if (result[i][0] != 0){
                strcat(final,result[i]);
                last = strlen(final);
                final[last] = 32;
            }
        }

        //printf("\nla phrase est : %s", final);
        strcpy(src, final);

        for ( i = 0; i < cptWord; ++i) {
            free(result[i]);
        }
        free(result);

    } else{
        printf("pas assez de ressources");
    }




   // split(size, src, result);

/*
    int color = 0;
    analyse(result, color, cptWord);


    //Affichage du tableau 2D
    for ( i = 0; i < cptWord; ++i) {
        if (result[i][0] != 0){
            printf("\n%s", result[i]);
        }
    }

    printf("\n-------------------");

    int last;
    for ( i = 0; i < cptWord; ++i) {
        if (result[i][0] != 0){
            strcat(final,result[i]);
            last = strlen(final);
            final[last] = 32;
        }
    }

    printf("\n la phrase est : %s", final);
*/
}
