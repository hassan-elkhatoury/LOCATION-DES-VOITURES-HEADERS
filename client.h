#ifndef CLIENT_H
#define CLIENT_H

// Client structure definition
typedef struct {
    char nom[100];
    char address[100];
    char phone[20];
    int age;
    char cin[50];
    char email[50];
    char password[50];
} Client;

// Voiture structure definition
typedef struct {
    char entreprise[50];
    char modele[50];
    float prix;
} Voiture;

// Options structure for menu options
typedef struct Options {
    char **ops;
    int len;
    char title[100];
} Options;

/**
 * @brief Checks if the email format is valid.
 * 
 * @param email Pointer to the email string.
 * @return int Returns 1 if valid, otherwise 0.
 */
int isValidEmail(const char *email);

/**
 * @brief Gets the password input from the user.
 * 
 * @param password Pointer to the password string.
 * @param maxLen Maximum length of the password.
 */
void getPassword(char *password, int maxLen);

/**
 * @brief Checks if the phone number format is valid.
 * 
 * @param phone Pointer to the phone number string.
 * @return int Returns 1 if valid, otherwise 0.
 */
int isValidPhoneNumber(const char *phone);

/**
 * @brief Checks if the given full name contains both first and last names.
 * 
 * @param fullName Pointer to the full name string.
 * @return int Returns 1 if valid, otherwise 0.
 */
int hasFirstAndLastName(char *fullName);

/**
 * @brief Combines the first and last names into a single string with an underscore.
 * 
 * @param fullName Pointer to the full name string.
 */
void combineNames(char *fullName);

/**
 * @brief Collects client information and saves it.
 */
void saisie();

/**
 * @brief Handles client login.
 */
void login();

/**
 * @brief Checks if the given full name contains both first and last names.
 * 
 * @param filename 
 * @param name 
 * @return int Returns 1 if valid, otherwise 0.
 */
int check_name_in_fileconst( char *filename, const char *name);

#endif // CLIENT_H
