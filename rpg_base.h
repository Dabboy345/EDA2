#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_NAME 30 
#define MAX_TXT 200 

typedef struct{ //Our data stucture for the skills
    char name[MAX_NAME];
    char description[MAX_TXT];
    int of_def; //1 for offensive, 0 for deffensive
    int dmg_skll;
    int modifier;
    int stats_plyr[3]; //dmg(0), def(1), hp(2)
    /*int dmg_plyr; 3 - 8       int def_plyr; 0 - 8       int hp_plyr; 25 - 50 */
}Skill;

typedef struct{ //This is our data structures for the character
    char name[MAX_NAME];
    int dmg; //12 - 32
    int def; //0 - 32
    int hp; //100 - 200
    Skill skill[4];
}Character;

typedef struct{ //This is our data structures for the Enemy
    char name[MAX_NAME];
    int dmg;
    int def;
    int hp;
    Skill skill[4];
}Enemy;

typedef struct{
    char question_txt[MAX_TXT];
    Option option[2];
}Decision;
//question text, options, number of options

typedef struct{
    char description[MAX_TXT];
    char pre_txt[MAX_TXT];
    Enemy enemy[3];
    char post_txt[MAX_TXT];
}Option;
//response text, narrative text (before battling the enemies), enemies (can be reused from other scenarios), 
//narrative text (after battling the enemies)

typedef struct{
    char name[MAX_NAME];
    char description[MAX_TXT];
    Decision decision[10];
}Scenario;
//name and description, and decision (or decision list).


void print_logo();//We will use this funtion to print our logo

void print_game_name();//We will use this function to print the game name

void print_menu(){//This will be the print function which will print the users menu
    printf("GAME LOGO");
    printf("GAME TITLE");
    printf("1. NEW GAME");
    printf("2. SAVE GAME");
    printf("3. Load GAME");
    printf("4. Exit GAME");
}
char get_Name_sk(){
    FILE *fp;
    fp = fopen("rpg_data.txt", "r");
    char s[MAX_TXT];
    char array[MAX_NAME];
    while(fgets(s, 10, fp)) {
        if(1==fscanf(fp, "Name_sk:%s\n", array)){
            //printf("%s\n", array);
            fgets(s, strlen(array), fp);
        }
    }
    fclose(fp); 
    return array;
}

