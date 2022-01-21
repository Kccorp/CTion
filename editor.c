//
// Created by Keissy on 19/01/2022.
//

void redColor (char* src){
    //printf("\n%s", src);
    char red [50]="\033[0;31m";
    strncpy(src, red, 10);
    //printf("\n%s", src);
}

void blueColor (char* src){
    //printf("\n%s", src);
    char red [50]="\033[0;34m";
    strncpy(src, red, 10);
    //printf("\n%s", src);
}

void reset (char* src){
    char red [50]="\033[0m";
    strncpy(src, red, 7);
}

void parse (char* src){
    int i,j = 0,k = 0;
    int size = strlen(src);
    char result [50][50] = {0};
    char final [150] = {0};


    //sépare les mots
    for (i = 0; i < size; ++i) {
        if (src[i] != 32){
            result[j][k] = src[i];
            result[j][k+1] = "\0";
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
