//
// Created by kbod on 16/02/2022.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "editor.c"

void remove_n(char *chaine, int size){
    int i;
    for ( i = 0; i < size; ++i) {
        if (chaine[i] == '\n'){
            chaine[i] = 0;
        }
    }
}

int main(int argc, char **argv){
    char *filename = "/mnt/c/Users/kbod/CLionProjects/cTion/config.txt"; //Full path from wsl
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Error: could not open file %s", filename);
        return 1;
    }

    // reading line by line, max 150 bytes/lines
    const int MAX_LENGTH = 150, MAX_ROW = 20;
    char line[MAX_LENGTH];
    int i,j=0,k=0;

    char window_size_x[4], window_size_y[4], hostDB[100], nameDB[50];
    char tmpResult[MAX_LENGTH][MAX_LENGTH];
    while (fgets(line, MAX_LENGTH, fp)) {


        //recupere les lignes du fichier
        if (strlen(line)>2){
            printf("%s", line);
            for (i = 0; i < strlen(line); i++) {
                if (line[i] != 58 && line[i]!=0){
                    tmpResult[j][k] = line[i];
                    k++;
                } else{
                    j++;
                    k = 0;
                }
            }
            tmpResult[j][k] = '\0';
            k=0;
            j++;
        }

    }

    // close the file
    fclose(fp);
    printf("\nfile closed\n");

    for (i = 0; i < MAX_ROW; ++i) {
        if (strcmp(tmpResult[i], "window_size_x")==0){
            strcpy(window_size_x,tmpResult[i+1]);
            printf("la variable window_size_x = %s", window_size_x);
            i++;
        } else if (strcmp(tmpResult[i], "window_size_y")==0){
            strcpy(window_size_y,tmpResult[i+1]);
            printf("la variable window_size_y = %s", window_size_y);
            i++;
        } else if (strcmp(tmpResult[i], "host")==0){
            strcpy(hostDB,tmpResult[i+1]);
            printf("la variable host = %s", hostDB);
            i++;
        } else if (strcmp(tmpResult[i], "database")==0){
            strcpy(nameDB,tmpResult[i+1]);
            printf("la variable nameDB = %s", nameDB);
            i++;
        }
    }

    return 0;
}
