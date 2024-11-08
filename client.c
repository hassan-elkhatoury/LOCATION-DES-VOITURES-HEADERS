#include "client.h" 
#include "colors.h" 
#include <stdio.h> 
#include <stdlib.h> 
#include <windows.h> 
#include <ctype.h>
#include <conio.h>
#include <string.h>
#include"connexion.h"
#include "display_mod.h"
#include "client.h"
 
 
int isValidEmail(const char *email) {
    const char *at = strchr(email, '@');  // pour trouver '@' dans email
    const char *dot = strrchr(email, '.'); // pour trouver '.' dans email

    // verifier si '@' trouvee, '.' trouvee, et '.' vient apres '@'
    return (at != NULL && dot != NULL && dot > at);
}

void getPassword(char *password, int maxLen) {
    int i = 0;
    char ch;
    while (i < maxLen - 1) {
        ch = getch();  
        if (ch == '\r') { 
            break;
        } else if (ch == '\b' && i > 0) {  
            i--;
            printf("\b \b");  
        } else if (isprint(ch)) {  
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0'; 
}

int isValidPhoneNumber(const char *phone) {
    if (strlen(phone) != 10) {
        return 0;  
    }
    for (int i = 0; i < 10; i++) {
        if (!isdigit(phone[i])) {
            return 0; 
        }
    }
    return 1;
}



int hasFirstAndLastName(char *fullName) {
    int spaceCount = 0;
    for (int i = 0; i < strlen(fullName); i++) {
        if (isspace(fullName[i])) {
            spaceCount++;
        }
    }
    return spaceCount > 0;
}

void combineNames(char *fullName) {
    char firstName[50], lastName[50], *token;
    char *words[50];
    int count = 0;

    token = strtok(fullName, " ");
    while (token != NULL) {
        words[count++] = token;
        token = strtok(NULL, " ");
    }

    if (count > 1) {
        strcpy(firstName, words[0]);
        strcpy(lastName, words[count - 1]);
        sprintf(fullName, "%s_%s", firstName, lastName);
    }
}

void saisie() {
    Client client1;
    FILE *fsaisie;
    FILE *fclient;
    char line[2000];
    char test_pass[50];
    const char *header = "Nom Complet\t\t\tAddress\tPhone\t\tAge\tCin\t\t\tEmail\t\t\t\tPassword\n";
    
    printf(CYAN);
    printf("Ecrire votre nom complet : \n");
    fgets(client1.nom, sizeof(client1.nom), stdin);
    client1.nom[strcspn(client1.nom, "\n")] = '\0';

    if (hasFirstAndLastName(client1.nom)) {
        combineNames(client1.nom);
    }

    printf("Ecrire votre address : \n");
    fgets(client1.address, sizeof(client1.address), stdin);
    client1.address[strcspn(client1.address, "\n")] = '\0'; 

    while (1) {
        printf("Ecrire votre phone : \n");
        scanf("%19s", client1.phone);

        if (isValidPhoneNumber(client1.phone)) {
            break;
        } else {
            printf(RED "Numero de telephone invalide! Assurez-vous qu'il contient exactement 10 chiffres.\n");
            setColor(cyan); 
        }
        }
    printf("Ecrire votre age : \n");
    scanf("%d", &client1.age);
    printf("Ecrire votre cin : \n");
    scanf("%s", client1.cin);

    while (1) {
        int email_exists = 0;
        printf("Ecrire votre email : \n");
        scanf("%49s", client1.email);

        while (!isValidEmail(client1.email)) {
            printf(RED "Email invalide! Assurez-vous qu'il contient '@' et '.' \n");
            setColor(cyan);  
            printf("Essayez de l'entrer a nouveau :\n");
            scanf("%49s", client1.email);
        }

        fsaisie = fopen("fclient.txt", "r");
        if (fclient != NULL) {
            while (fgets(line, sizeof(line), fsaisie)) {
                if (strstr(line, client1.email) != NULL) {
                    email_exists = 1;
                    break;
                }
            }
            fclose(fsaisie);
        }

        if (email_exists) {
            printf(RED "Cet email est deja existe !!\n");
            setColor(cyan);
            printf("Essayez de l'entrer a nouveau !:\n");
        } else {
            break;
        }
    }

    int valide;
    printf("Ecrire votre password : \n");
    getPassword(client1.password, sizeof(client1.password));
    printf("\n");
    printf("Ecrire votre password a nouveau : \n");
    getPassword(test_pass, sizeof(test_pass));
    printf("\n");

    while (1) {
        if (strcmp(client1.password, test_pass) == 0) {
            valide = 1;
            break;
        } else {
            printf(RED "Les deux password sont different \n");
            printf(CYAN "Essayez de l'entrer a nouveau !:\n");
            getPassword(test_pass, sizeof(test_pass));
        }
    }

    if (test_pass != NULL) {
        strcpy(client1.password, test_pass);
    }
    if (valide == 1) {
        printf(GREEN "Merci! Votre compte a ete cree avec succes.\n");
        printf(CYAN "Veuillez essayer de vous connecter en selectionnant l'option :" MAGENTA " J'ai deja un compte.\n");
        system("pause");
    }

    fsaisie = fopen("fsaisie.txt", "a+");
    if (fsaisie == NULL) {
        printf(RED "Error in opening file");
        exit(1);
    }
    fseek(fsaisie, 0, SEEK_END);
    if (ftell(fsaisie) == 0) {
        fprintf(fsaisie, "%s", header);
        fprintf(fsaisie, "%s", "-----------------------------------------------------------------------------------------------------\n");
    }
    fprintf(fsaisie, "%s\t%s\t%s\t%d\t%s\t%s\t%s\n", client1.nom, client1.address, client1.phone, client1.age, client1.cin, client1.email, client1.password);
    fclose(fsaisie);

    fclient = fopen("fclient.txt", "a+");
    if (fclient == NULL) {
        printf(RED "Error in opening file");
        exit(1);
    }
    fprintf(fclient, "%s\t\t%s\t\t%s\n", client1.nom, client1.email, client1.password);
    fclose(fclient);

    display_car_models_menu(client1.nom);
}

void login() {
    FILE *fclient;
    char email[50];
    char password[50];
    char line[2000];
    Client client1;

    while (1) {
        setColor(purple);
        printf("Enter your email: ");
        scanf("%49s", email);
        printf("Enter your password: ");
        getPassword(password, sizeof(password));
        printf("\n");

        fclient = fopen("fclient.txt", "r");
        if (fclient == NULL) {
            printf(RED "Error opening the file.\n");
            return;
        }

        int authenticated = 0;
        while (fgets(line, sizeof(line), fclient)) {
            char fileEmail[50], filePassword[50], fileNom[100];
            sscanf(line, "%s %49s %49s", fileNom, fileEmail, filePassword);

            if (strcmp(email, fileEmail) == 0 && strcmp(password, filePassword) == 0) {
                authenticated = 1;
                strncpy(client1.nom, fileNom, sizeof(client1.nom) - 1);
                client1.nom[sizeof(client1.nom) - 1] = '\0';
                break;
            }
        }
        fclose(fclient);

        if (authenticated) {
            display_car_models_menu(client1.nom);
            return;
        } else {
            printf(RED "\nInvalid email or password. Please try again.\n" RESET);
        }
    }
}
