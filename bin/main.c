#include "checkers.h"
#include "stack.h"


// ************File used to call & run the functions************

int stop = 0;

void print_image(FILE *fptr)
{
    char read_string[MAX_LEN];

    while(fgets(read_string,sizeof(read_string),fptr) != NULL)
        printf("%s",read_string);
}

void showRanking(){
    system("cls");
    int c;
    FILE *file;
    file = fopen(ranking, "r");
    printf("\n");
    printf("=====RANKING=====\n");

    if (file) {
        while ((c = getc(file)) != EOF){
            putchar(c);
        }

    fclose(file);
    }
    printf("\n=================\n");

    printf("\nPress any key to continue!\n");;
    getch();
}

void showCredits(){
    system("cls");
    FILE *file = NULL;

    if((file = fopen(credits,"rw+")) == NULL)
    {
        fprintf(stderr,"Nao foi possivel encontrar o arquivo %s\n",credits);

    }

    print_image(file);
    fclose(file);
    printf("Press any key to continue!");;
    getch();
}

int introduction()
{
    system("cls");
    int opt = 0;
    printf("\n\n\n +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n"
           " ____________________________________________________________________________\n\n"
           "   ######  ##     ## ########  ######  ##    ## ######## ########   ######\n"
           "  ##    ## ##     ## ##       ##    ## ##   ##  ##       ##     ## ##    ##\n"
           "  ##       ##     ## ##       ##       ##  ##   ##       ##     ## ##       \n"
           "  ##       ######### ######   ##       #####    ######   ########   ######  \n"
           "  ##       ##     ## ##       ##       ##  ##   ##       ##   ##         ## \n"
           "  ##    ## ##     ## ##       ##    ## ##   ##  ##       ##    ##  ##    ##\n"
           "   ######  ##     ## ########  ######  ##    ## ######## ##     ##  ######  \n"
           " ____________________________________________________________________________\n\n"
           " +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        printf("\n1 - Play");
        printf("\n2 - Ranking");
        printf("\n3 - Credits");
        printf("\n4 - Exit");
        printf("\nInput one of the options? (1-4)\n");
        scanf("%d", &opt);
        return opt;
}

int main(void){
   
   while(stop == 0){
        int option = introduction();
        switch (option)
        {
        case 1:
            game();
            continue;
        case 2:
            showRanking();
            continue;
        case 3:
            showCredits();
            continue;
        case 4:
            stop = 1;
        }
   }
  
}
