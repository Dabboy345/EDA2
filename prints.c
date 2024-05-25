#include "prints.h"

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
    print_game_name();
    printf("\n");
    printf("1. New GAME\n");
    printf("2. Load GAME\n");
    printf("3. Exit GAME\n");
}


void print_decision(Decision *choice, Character* plyr) {
    printf("%s\n", choice->option.description);
    printf("%s\n", choice->option.pre_txt);
    if (strcmp(choice->option.enemy.name, "None") == 0) {
        printf("No enemy\n");
    } else {
        printf("Enemy is %s with skills:\n1.%s2.%s3.%s4.%s\n",
            choice->option.enemy.name,
            choice->option.enemy.skill[0],
            choice->option.enemy.skill[1],
            choice->option.enemy.skill[2],
            choice->option.enemy.skill[3]);
        while(combat(plyr, &choice->option.enemy, 20)==2){
            for(int i=0;i<4;i++){plyr->stats[2]+=plyr->skill[i].stats_plyr[2];}//Reset health
        }

    }
    printf("%s\n", choice->option.post_txt);
    printf("1.%s\n", choice->option.option1);
    printf("2.%s\n", choice->option.option2);
};

void print_menu_option(){
    printf("Please select the next options\n");
    printf("Press 1 for first option\n");
    printf("Press 2 for second option\n");
    printf("Press 3 to save the progress\n");
    printf("Press 4 to exit\n");
}