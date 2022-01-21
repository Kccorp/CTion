//
// Created by Keiss on 20/01/2022.
//

void remove_n(char *chaine, int size);
void vider_buffer(void);

void main_menu (int *choice){
    while (*choice > 3 || *choice <= 0 ){
        printf("\n1)Se connecter\n2)S'inscrire\n3)Exit\n");
        scanf("%d", choice);
        vider_buffer();
    }
}

void ask_pseudo (char *pseudo){
    do {
        printf("\nSe connecter\n\nPseudo : ");
        fgets(pseudo, 25, stdin);
        remove_n(pseudo, 25);
    } while (pseudo[0] == 0);
}

void ask_password (char *password){
    do {
        printf("\nSe connecter\n\nMot de passe : ");
        fgets(password, 100, stdin);
        remove_n(password, 100);
    } while (password[0] == 0);
}

int check_password(char *pwd, char *checkPwd, int *connected){
    if (checkPwd[0] != 0){
        //printf("\nle mot de passe de %s est %s", pseudo, checkPwd);
        if (strcmp(pwd, checkPwd) == 0){
            printf("\nle mdp est correct connexion validé");
            return *connected = 1;
        } else {
            printf("\nle mdp est incorrect connexion refusé\n");
            return 0;
        }
    }
}

void register_pseudo (char *pseudo, int *verif){
    int check=0;
    do {
        if (check==1){
            printf("\nS'inscrire\n\033[0;31m(le pseudo ne doit pas etre vide et minimum 4 caractères)\033[0m\nPseudo : ");
        } else if (*verif==2){
            printf("\nS'inscrire\n\033[0;31m(pseudo déjà existant)\033[0m\n\nPseudo : ");
        }else {
            printf("\nS'inscrire\n\nPseudo : ");
        }
        fgets(pseudo, 25, stdin);
        remove_n(pseudo, 25);
        check=1;
    } while (pseudo[0] == 0 || strlen(pseudo)<4);
}

void register_password (char *password){
    int i;
    int checkMaj=0, checkMin=0, checkNumber=0, check=0;
    do {
        if (check==1){
            printf("\nS'inscrire\n\033[0;31m(le mot de passe ne doit pas etre vide, minimum 5 caractères, une majuscule, une minuscule et un chiffre)\033[0m\nMot de passe : ");
        } else {
            printf("\nS'inscrire\n\nMot de passe : ");
        }

        fgets(password, 100, stdin);
        remove_n(password, 100);

        for (i = 0; i < strlen(password); ++i) {
            if (password[i] >= 65 && password[i] <= 90)checkMaj=1;
            if (password[i] >= 97 && password[i] <= 122)checkMin=1;
            if (password[i] >= 48 && password[i] <= 57)checkNumber=1;
        }
        check=1;

    } while (password[0] == 0 || strlen(password)<5 || strlen(password)>100 || checkNumber == 0 || checkMaj == 0 || checkMin == 0);
}