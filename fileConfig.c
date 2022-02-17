//
// Created by kbod on 16/02/2022.
//

void fileConfig(char *window_size_x, char *window_size_y,char *hostDB,char *nameDB){
    char *filename = "../config.txt"; //path from current dir
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Erreur: Impossible d'ouvrir le fichier %s", filename);
        exit(1);
    }

    // reading line by line, max 150 bytes/lines
    const int MAX_LENGTH = 150, MAX_ROW = 20;
    char line[MAX_LENGTH];
    int i,j=0,k=0;


    char tmpResult[MAX_LENGTH][MAX_LENGTH];
    while (fgets(line, MAX_LENGTH, fp)) {


        //recupere les lignes du fichier
        if (strlen(line)>2){
            for (i = 0; i < strlen(line); i++) {
                if (line[i] != 58 && line[i] != EOF && line[i] != 59){
                    tmpResult[j][k] = line[i];
                    k++;
                } else{
                    k++;
                    tmpResult[j][k] = '\0';
                    j++;
                    k = 0;
                }
            }

            k=0;
            j++;
        }

    }

    // close the file
    if (fclose(fp)!=0) {
        printf("fichier non fermé");
    }else{
        printf("\nfile closed\n");;
    }

    //set variables
    for (i = 0; i < MAX_ROW; ++i) {
        if (strcmp(tmpResult[i], "window_size_x")==0){
            strcpy(window_size_x,tmpResult[i+1]);
            //printf("\nla variable window_size_x = %s", window_size_x);
            //printf("\nla size = %d", strlen(tmpResult[i+1]));
            i++;
        } else if (strcmp(tmpResult[i], "window_size_y")==0){
            strcpy(window_size_y,tmpResult[i+1]);
            //printf("la variable window_size_y = %s", window_size_y);
            i++;
        } else if (strcmp(tmpResult[i], "host")==0){
            strcpy(hostDB,tmpResult[i+1]);
            //printf("la variable host = %s", hostDB);
            i++;
        } else if (strcmp(tmpResult[i], "database")==0){
            strcpy(nameDB,tmpResult[i+1]);
            //printf("la variable nameDB = %s", nameDB);
            i++;
        }
    }
}
