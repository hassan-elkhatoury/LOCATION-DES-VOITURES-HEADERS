
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>
#include <conio.h>
#include <string.h>
#include "client.h"
#include "colors.h"

int visible_length(const char *text) {
    int len = 0;
    int in_escape = 0;
    
    while (*text) {
        if (*text == '\033') {  
            in_escape = 1;
        } else if (in_escape && *text == 'm') {  
            in_escape = 0;
        } else if (!in_escape) {
            len++;  
        }
        text++;
    }
    return len;
}

void print_centered(const char *text) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    
    int console_width = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    int text_len = visible_length(text);

    int padding = (console_width - text_len) / 2;

    for (int i = 0; i < padding; i++) {
        printf(" ");
    }
    printf("%s\n", text);
}

void draw(int op, Options options) {
    system("cls"); 
    char line[110];
    snprintf(line, sizeof(line), BOLD "%s\n", options.title);
    print_centered(line);
    for (int i = 0; i < options.len; i++) { 
        sprintf(line, ITALIC "%s%s%s" RESET, op == i ? BLUE "[" : WHITE " ", options.ops[i], op == i ? BLUE "]" : WHITE " ");
        print_centered(line);  
    }
}

int select_menu(Options options) {
    int current_option = 0;
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);  
    DWORD mode;
    GetConsoleMode(hInput, &mode);
    SetConsoleMode(hInput, mode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT));

    draw(current_option, options);

    INPUT_RECORD input;
    DWORD events;
    while (1) {
        ReadConsoleInput(hInput, &input, 1, &events);  // Read input from console
        if (input.EventType == KEY_EVENT && input.Event.KeyEvent.bKeyDown) {
            switch (input.Event.KeyEvent.wVirtualKeyCode) {
                case VK_UP:
                    if (current_option > 0) {
                        current_option--;
                        draw(current_option, options);
                    }
                    break;
                case VK_DOWN:
                    if (current_option < options.len-1) {
                        current_option++;
                        draw(current_option, options);
                    }
                    break;
                case VK_RETURN:  
                    return current_option;
            }
        }
    }
}
