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
#include <time.h>>
 
 
bool isValidEmail(const char *email) {
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
    char test_pass[50];
    const char *header = "Nom Complet\t\t\tAddress\tPhone\t\tAge\tCin\t\t\tEmail\t\t\t\tPassword\n";
    char *line = malloc(2000 * sizeof(char)); // Allouer dynamiquement la mémoire pour line

    if (line == NULL) {
        fprintf(stderr, "Echec de l'allocation de memoire\n");
        return;
    }
    setColor(cyan);
    printf("Ecrire votre nom complet : \n" );
    fgets(client1.nom, sizeof(client1.nom), stdin);
    client1.nom[strcspn(client1.nom, "\n")] = '\0';

    if (hasFirstAndLastName(client1.nom)) {
        combineNames(client1.nom);
    }

    printf("Ecrire votre adresse : \n");
    fgets(client1.address, sizeof(client1.address), stdin);
    client1.address[strcspn(client1.address, "\n")] = '\0';

    // Boucle pour valider le numéro de téléphone
    while (1) {
        printf("Ecrire votre numero de telephone : \n");
        scanf("%19s", client1.phone);

        if (isValidPhoneNumber(client1.phone)) {
            break;
        } else {
            printf(RED "Numero de telephone invalide! Assurez-vous qu'il contient exactement 10 chiffres.\n" RESET);
            setColor(cyan);
        }
    }

    printf("Ecrire votre age : \n");
    scanf("%d", &client1.age);
    printf("Ecrire votre CIN : \n");
    scanf("%s", client1.cin);

    // Vérification de l'unicité de l'email
    while (1) {
        int email_exists = 0;
        printf("Ecrire votre email : \n");
        scanf("%49s", client1.email);

        while (!isValidEmail(client1.email)) {
            printf(RED "Email invalide! Assurez-vous qu'il contient '@' et '.' \n" RESET);
            setColor(cyan);
            printf("Essayez de l'entrer a nouveau :\n");
            scanf("%49s", client1.email);
        }

        // Ouverture du fichier pour vérifier l'existence de l'email
        fsaisie = fopen("fsaisie.txt", "r");
        if (fsaisie == NULL) {
            printf(RED "Erreur lors de l'ouverture du fichier.\n" RESET);
            free(line);  // Libérer la mémoire en cas de retour anticipé
            return;
        }

        while (fgets(line, 2000, fsaisie)) {
            if (strstr(line, client1.email) != NULL) {
                email_exists = 1;
                break;
            }
        }
        fclose(fsaisie);

        if (email_exists) {
            printf(RED "Cet email existe deja !!\n" RESET);
            setColor(cyan);
            printf("Essayez de l'entrer à nouveau !:\n");
        } else {
            break;
        }
    }

    // Validation du mot de passe
    printf("Ecrire votre mot de passe : \n");
    getPassword(client1.password, sizeof(client1.password));
    printf("\n");

    while (1) {
    setColor(cyan);
        printf("Ecrire votre mot de passe a nouveau : \n");
        getPassword(test_pass, sizeof(test_pass));
        printf("\n");

        if (strcmp(client1.password, test_pass) == 0) {
            break;
        } else {
            printf(RED "Les deux mots de passe sont differents\n" RESET);
        }
    }

    // Ajouter les informations du client validées au fichier
    fsaisie = fopen("fsaisie.txt", "a+");
    if (fsaisie == NULL) {
        printf(RED "Erreur lors de l'ouverture du fichier fsaisie.txt\n" RESET);
        free(line);  // Libérer avant de quitter
        exit(1);
    }
    fseek(fsaisie, 0, SEEK_END);

    if (ftell(fsaisie) == 0) { // Écrire l'en-tête seulement si le fichier est vide
        fprintf(fsaisie, "%s", header);
        fprintf(fsaisie, "%s", "-----------------------------------------------------------------------------------------------------\n");
    }

    fprintf(fsaisie, "%s\t%s\t%s\t%d\t%s\t%s\t%s\n", client1.nom, client1.address, client1.phone, client1.age, client1.cin, client1.email, client1.password);
    fclose(fsaisie);

    // Ajouter également au fichier fclient.txt
    fclient = fopen("fclient.txt", "a+");
    if (fclient == NULL) {
        printf(RED "Erreur lors de l'ouverture du fichier fclient.txt\n" RESET);
        free(line);  // Libérer avant de quitter
        exit(1);
    }
    fprintf(fclient, "\n%s\t\t%s\t\t%s", client1.nom, client1.email, client1.password);
    fclose(fclient);

    printf(GREEN "Merci! Votre compte a ete cree avec succes.\n" RESET);
    printf(CYAN "Veuillez essayer de vous connecter en selectionnant l'option :" MAGENTA BOLD ITALIC " J'ai deja un compte.\n" RESET);
    printf(GREEN "Ou bien appuyez sur Entree pour continuer." RESET);
    getch();
    display_car_models_menu(client1.nom);
    free(line); // Libérer line après son utilisation
    
}


void login() {
    FILE *fclient;
    char email[50];
    char password[50];
    Client client1;
    char *line = malloc(2000 * sizeof(char)); // Dynamic allocation for line
    if (line == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return; // Return immediately if allocation fails
    }
   
    while (1) {
        setColor(purple);
        printf("Enter your email: ");
        scanf("%49s", email);
        printf("Enter your password: ");
        getPassword(password, sizeof(password));
        printf("\n");

        fclient = fopen("fclient.txt", "r");
        if (fclient == NULL) {
            printf(RED "Error opening the file.\n" RESET);
            free(line); // Free line before returning
            return;
        }

        int authenticated = 0;
        while (fgets(line, 2000, fclient)) { // Specify the size for fgets
            char fileEmail[50], filePassword[50], fileNom[100];

            if (sscanf(line, "%49[^\t]\t%49[^\t]\t%49s", fileNom, fileEmail, filePassword) == 3) {
                // Check if the email and password match
                if (strcmp(email, fileEmail) == 0 && strcmp(password, filePassword) == 0) {
                    authenticated = 1;
                    strncpy(client1.email, fileEmail, sizeof(client1.email) - 1);
                    client1.email[sizeof(client1.email) - 1] = '\0'; 
                    strncpy(client1.nom, fileNom, sizeof(client1.nom) - 1);
                    client1.nom[sizeof(client1.nom) - 1] = '\0';
                    break;
                }
            }
        }
        
        fclose(fclient); // Close the file after reading

        if (authenticated) {
            display_car_models_menu(client1.nom);
            free(line); // Free line before returning
            return;
        } else {
            printf(RED "\nInvalid email or password. Please try again.\n" RESET);
        }
    }
    free(line); // Free line after the loop ends if no successful login
}
