#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>
#include <conio.h>
#include <string.h>
#include "client.h"
#include "colors.h"
#include "interface.h"
#include "frst_menu.h"

void connexion() {
    Options options;
    char *LOGIN_OPTIONS[] = {
        BOLD "Cree un compte",
        BOLD "J'ai deja un compte",
        BOLD "Retour au menu principal",
        RED BOLD "Quitter le programme"
    };
    strcpy(options.title, YELLOW "MENU DE CONNECTION");
    options.ops = LOGIN_OPTIONS;
    options.len = sizeof(LOGIN_OPTIONS) / sizeof(LOGIN_OPTIONS[0]);

    int option = select_menu(options);
    switch (option) {
        case 0:
            saisie();
            break;
        case 1:
            login();
            break;
        case 2: 
            frstmenu();
        case 3:
        exit(0);
        default:
            printf("Option invalide.\n");
            break;
    } 
}
