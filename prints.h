#include "common.h"
void print_game_logo(){ //We will use this funtion to print our logo
    
}
void print_game_name(){ //We will use this funtion to print our logo
    const char *ascii_art = 
    "                         ___                                                ___                              \n"
    "                        (   )                                              (   )                             \n"
    " ___  ___  ___   .--.    | |    .--.      .--.    ___ .-. .-.     .--.      | |_       .--.                 \n"
    "(   )(   )(   ) /    \\   | |   /    \\    /    \\  (   )   '   \\   /    \\    (   __)    /    \\                \n"
    " | |  | |  | | |  .-. ;  | |  |  .-. ;  |  .-. ;  |  .-.  .-. ; |  .-. ;    | |      |  .-. ;               \n"
    " | |  | |  | | |  | | |  | |  |  |(___) | |  | |  | |  | |  | | |  | | |    | | ___  | |  | |               \n"
    " | |  | |  | | |  |/  |  | |  |  |      | |  | |  | |  | |  | | |  |/  |    | |(   ) | |  | |               \n"
    " | |  | |  | | |  ' _.'  | |  |  | ___  | |  | |  | |  | |  | | |  ' _.'    | | | |  | |  | |               \n"
    " | |  ; '  | | |  .'.-.  | |  |  '(   ) | '  | |  | |  | |  | | |  .'.-.    | ' | |  | '  | |               \n"
    " ' `-'   `-' ' '  `-' /  | |  '  `-' |  '  `-' /  | |  | |  | | '  `-' /    ' `-' ;  '  `-' /               \n"
    "  '.__.'.__.'   `.__.'  (___)  `.__,'    `.__.'  (___)(___)(___) `.__.'      `.__.    `.__.'                 \n"
    "                                                                             .-.                         .-.  \n"
    "   .-..    ___ .-.      .--.       .--.      .--.    ___ .-. .-.     .--.   ( __)   .--.       .--.    ( __) \n"
    "  /    \\  (   )   \\    /    \\    /  _  \\    /    \\  (   )   '   \\   /    \\  (''\")  /    \\    /  _  \\   (''\") \n"
    " ' .-,  ;  | ' .-. ;  |  .-. ;  . .' `. ;  |  .-. ;  |  .-.  .-. ; |  .-. ;  | |  |  .-. ;  . .' `. ;   | |  \n"
    " | |  . |  |  / (___) | |  | |  | '   | |  | |  | |  | |  | |  | | | |  | |  | |  | |  | |  | '   | |   | |  \n"
    " | |  | |  | |        | |  | |  _\\_`.(___) | |  | |  | |  | |  | | | |  | |  | |  | |  | |  _\\_`.(___)  | |  \n"
    " | |  | |  | |        | |  | | (   ). '.   | |  | |  | |  | |  | | |  | |  | |  | |  | | (   ). '.    | |  \n"
    " | |  ' |  | |        | '  | |  | |  `\\ |  | '  | |  | |  | |  | | '  | |  | |  | '  | |  | |  `\\ |   | |  \n"
    " | `-'  '  | |        '  `-' /  ; '._,' '  '  `-' /  | |  | |  | | '  `-' /  | |  '  `-' /  ; '._,' '   | |  \n"
    " | \\__.'  (___)        `.__.'    '.___.'    `.__.'  (___)(___)(___) `.__.'  (___)  `.__.'    '.___.'   (___) \n"
    " | |                                                                                                        \n"
    "(___)                                                                                                       \n";

    // Print the ASCII Art
    printf("%s", ascii_art);
}

void print_menu(){//This will be the print function which will print the users menu
    print_game_logo();
    print_game_name();
    printf("\n");
    printf("1. NEW GAME\n");
    printf("2. SAVE GAME\n");
    printf("3. Load GAME\n");
    printf("4. Exit GAME\n");
}

void print_node(); 