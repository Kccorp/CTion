//
// Created by Keiss on 24/02/2022.
//

void get_page(char *url, char *file_name)
{
    CURL* easyhandle = curl_easy_init();

    curl_easy_setopt( easyhandle, CURLOPT_URL, url ) ;

    FILE* file = fopen( file_name, "w");

    curl_easy_setopt( easyhandle, CURLOPT_WRITEDATA, file) ;

    curl_easy_perform( easyhandle );

    curl_easy_cleanup( easyhandle );

    fclose(file);

}

void scrap(){
    char *filename = "../http.txt"; //path from current dir

    get_page( "https://steamcharts.com/", filename ) ;

    const int MAX_ROW = 330;
    char scrapline[MAX_ROW];
    int i = 1;
    char jeu1[255], jeu2[255], jeu3[255];

    FILE *fp = fopen(filename, "r");
    while (fgets(scrapline, MAX_ROW, fp)) {
        if(i < MAX_ROW){
            if(i == 296){
                printf("\nla ligne : %s", scrapline);
                strcpy(jeu1, scrapline);
            }
            if(i == 307){
                printf("\nla ligne : %s", scrapline);
                strcpy(jeu2, scrapline);
            }
            if(i == 318){
                printf("\nla ligne : %s", scrapline);
                strcpy(jeu3, scrapline);
            }
        }
        i++;
    }

    // close the file
    if (fclose(fp) != 0) {
        printf("fichier non fermé");
    }

    printf("\njeu 1 = %s \n jeu2 = %s \n jeu3 = %s", jeu1, jeu2, jeu3);
}