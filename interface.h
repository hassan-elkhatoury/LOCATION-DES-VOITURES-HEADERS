#ifndef INTERFACE_H
#define INTERFACE_H
#include "client.h"
#include "colors.h"

/**
 * @brief Calculates the visible length of a text with ANSI escape codes.
 * 
 * @param text Pointer to the text string.
 * @return int The length of the visible text.
 */
int visible_length(const char *text);

/**
 * @brief Prints the given text centered in the console.
 * 
 * @param text Pointer to the text string.
 */
void print_centered(const char *text);

/**
 * @brief Draws the menu with the given options.
 * 
 * @param op Currently selected option index.
 * @param options Menu options structure.
 */
void draw(int op, Options options);

/**
 * @brief Displays a menu and returns the selected option index.
 * 
 * @param options
 * @return int Selected option index.
 */
int select_menu(Options options);

#endif