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

int check_password(char *pwd, char *checkPwd, int connected){
    if (checkPwd[0] != 0){
        //printf("\nle mot de passe de %s est %s", pseudo, checkPwd);
        if (strcmp(pwd, checkPwd) == 0){
            printf("\nle mdp est correct connexion validé");
            return connected== 1;
        } else {
            printf("\nle mdp est incorrect connexion refusé");
            exit(1);
        }
    }
}
