//
// Created by Keiss on 20/01/2022.
//


void vider_buffer(void);
void remove_n(char *chaine, int size);

void main_menu (int *choice){
    while (*choice > 3 || *choice <= 0 ){
        printf("\n1)Se connecter\n2)S'inscrire\n3)Exit\n");
        scanf("%d", choice);
        vider_buffer();
    }
}

void check_password(char *pwd, char *checkPwd, int *connected){
    if (checkPwd[0] != 0){
        //printf("\nle mot de passe de %s est %s", pseudo, checkPwd);
        if (strcmp(pwd, checkPwd) == 0){
            printf("\nle mdp est correct connexion validé");
            *connected = 1;
        } else {
            printf("\nle mdp est incorrect connexion refusé\n");
        }
    }
}

void verify_password (char *password, int *check){
    int i;
    int checkMaj=0, checkMin=0, checkNumber=0;

    remove_n(password, 100);

    for (i = 0; i < strlen(password); ++i) {
        if (password[i] >= 65 && password[i] <= 90)checkMaj=1;
        if (password[i] >= 97 && password[i] <= 122)checkMin=1;
        if (password[i] >= 48 && password[i] <= 57)checkNumber=1;
    }

    if (checkMaj == 1 && checkMin == 1 && checkNumber == 1)*check=1;
}