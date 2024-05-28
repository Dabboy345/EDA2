#include "prints.h"

void print_game_name(){ //To print name of our game
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
    printf("2. Continue GAME\n");   
    printf("3. Load GAME\n");
    printf("4. Exit GAME\n");
}

void print_skills(Skill* skills){
    printf("\nType 0 to see skills by default\n");
    printf("Type 1 to see skills ordered by attack stat\n");
    printf("Type 2 to see skills ordered by defense stat\n");
    printf("Type 3 to see skills ordered by health stat\n");
    int n = get_valid_input(0,3);
    printf("\n");
    if(n==0){
        for(int i = 0; i<21; i++){
        printf("%d.%s",i+1, skills[i].name);
        }
    }else{order_skills(n, skills);}
    printf("\n");
}

void print_decision(Decision *choice, Character* plyr, Scenario* scene) { //This fucntion helps us to print the informacion that we have in the decision
    printf("%s\n", choice->option.description);//Print the description
    printf("%s\n", choice->option.pre_txt);//Print pre text
    if (strcmp(choice->option.enemy.name, "None") == 0) {//If there is no enemy then we don't print anything 
    } else {     //If there is a enemy we print the enemy name and skills
        printf("Enemy is %s with skills:\n1.%s2.%s3.%s4.%s\n",
            choice->option.enemy.name,
            choice->option.enemy.skill[0],
            choice->option.enemy.skill[1],
            choice->option.enemy.skill[2],
            choice->option.enemy.skill[3]);
        while(combat(plyr, &choice->option.enemy, 20)==2){ 
            printf("\nDo you want to change skills? Yes->0, No->1: ");
            if(get_valid_input(0, 1)==0){
                Skill *skill = (Skill*)calloc(MAX_NUMBER_SKILL_PLAYER, sizeof(Skill));
                if(skill == NULL){
                    printf("Memory allocation failed\n");
                    return;
                }
                for(int i =0; i<MAX_NUMBER_SKILL_PLAYER;i++){
                    get_skill(&skill[i], i);
                }
                choose_skill(skill, plyr);
            }
            plyr->stats[2] = 0;
            for(int i=0;i<4;i++){plyr->stats[2]+=plyr->skill[i].stats_plyr[2];}//Reset health
            save_game(scene, plyr, "auto_save.txt");
        }
    }
    int a = (choice->option.option1[2]=='E' && choice->option.option1[6]=='n')? 0:1; //We check if the recived information is for end node or not 
    int b = (choice->option.option2[2]=='E' && choice->option.option2[6]=='n')? 0:1;
    printf("%s\n", choice->option.post_txt);//We print the post text 
    if(a==1 || b==1){
        printf("1.%s\n", choice->option.option1);//We print the description for option 1 
        printf("2.%s\n", choice->option.option2);//We print the description for option 2
    }
};

void print_menu_option(){ //We print what the user is able to do after a decisiom and combat 
    printf("Please select the next options\n");
    printf("Press 1 for first option\n");
    printf("Press 2 for second option\n");
    printf("Press 3 to save the progress\n");
    printf("Press 4 to exit\n");
}