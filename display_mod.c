#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>
#include <conio.h>
#include <string.h>
#include "client.h"
#include "colors.h"
#include "interface.h"
#include "connexion.h"

void display_car_models_menu(const char *nom) {
    Options options;
    char *CAR_OPTIONS[] = {
        BOLD "Modeles de voiture",
        BOLD "Recherche d'une voiture",
        BOLD "Reservation d'une voiture",
        BOLD "Retour au menu de connexion",
       RED BOLD "Quitter le programme"
    };
    snprintf(options.title, sizeof(options.title), YELLOW "BIENVENUE, %s!", nom);
    options.ops = CAR_OPTIONS;
    options.len = sizeof(CAR_OPTIONS) / sizeof(CAR_OPTIONS[0]);

    int option = select_menu(options);
   
    switch (option) {
        case 0:
            printf("encoure....\n");
              system("pause");
        case 1:
            printf("encoure.....\n");
            system("pause");
        case 2:
        printf("encoure......\n");
        system("pause");
        case 3: 
        connexion(nom);
        case 4:
        exit(0);
        default:
            printf("Option invalide.\n");
            break;
    } 
}
