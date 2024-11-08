#ifndef COLORS_H
#define COLORS_H

// Define ANSI color codes
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"
#define CYAN        "\033[36m"
#define WHITE       "\033[37m"

// Define ANSI codes for styles
#define BOLD        "\033[1m"
#define ITALIC      "\033[3m"
#define RESET       "\033[0m"

// Windows Console Color Defines
#define black           0
#define blue            1
#define green           2
#define cyan            3  
#define red             4
#define purple          5
#define yellow          6
#define white           7
#define gray            8
#define light_blue      9
#define light_green     10
#define light_aqua      11
#define light_red       12
#define light_purple    13
#define light_yellow    14
#define bright_white    15

void setColor(int color);

#endif // COLORS_H
