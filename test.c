#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <graphics.h>
#include "editor.c"


int main(int argc, char **argv) {


    char phrase [20000] = "Je blue[ suis ] un red[ text  cool ] super" ;
    fgets(phrase, 20000-1, stdin);

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
   parse(phrase);
}
