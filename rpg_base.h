#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include"rpg_game.h"
#define MAX_NAME 30 
#define MAX_TXT 200 

void print_menu(){//This will be the print function which will print the users menu
    printf("GAME LOGO\n");
    printf("GAME TITLE\n");
    printf("1. NEW GAME\n");
    printf("2. SAVE GAME\n");
    printf("3. Load GAME\n");
    printf("4. Exit GAME\n");
}

typedef struct{ //Our data stucture for the skills
    char name[MAX_NAME];
    char description[MAX_TXT];
    int of_def; //1 for offensive, 0 for deffensive
    int dmg_skll;// 10-35
    char modifier[MAX_NAME];
    int stats_plyr[3]; //dmg(0), def(1), hp(2)
    /*int dmg_plyr; 1-2       int def_plyr; 0 - 8       int hp_plyr; 25 - 50 */
}Skill;

typedef struct{ //This is our data structures for the character
    char name[MAX_NAME];
    int stats[3];//dmg(0), def(1), hp(2)
    //int dmg; 12 - 32      int def; 0 - 32       int hp; 100 - 200
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
    char description[MAX_TXT];
    char pre_txt[MAX_TXT];
    Enemy enemy[3];
    char post_txt[MAX_TXT];
}Option;
//response text, narrative text (before battling the enemies), enemies (can be reused from other scenarios), 
//narrative text (after battling the enemies)

typedef struct{
    char question_txt[MAX_TXT];
    Option* option[2];
}Decision;
//question text, options, number of options

typedef struct{
    char name[MAX_NAME];
    char description[MAX_TXT];
    Decision decision[10];
}Scenario;
//name and description, and decision (or decision list).


void print_logo();//We will use this funtion to print our logo

void print_game_name();//We will use this function to print the game name

void get_skill(Skill skill[]){
    FILE *fp;
    int i = 0;
    char c[MAX_NAME];
    fp = fopen("list_skill.txt", "r");
    while("SKILLS"!=fgets(c, MAX_NAME, fp)){;};
    while(!feof(fp)){
        fgets((skill[i]).name, MAX_NAME, fp);
        fgets((skill[i]).description, MAX_TXT, fp);
        fscanf(fp, "%d\n", &(skill[i]).of_def);
        fscanf(fp, "%d\n", &(skill[i]).dmg_skll);
        fgets((skill[i]).modifier, MAX_TXT, fp);
        fscanf(fp, "%d, %d, %d\n", &(skill[i]).stats_plyr[0], &(skill[i]).stats_plyr[1], &(skill[i]).stats_plyr[2]);
        
        printf("______%s\n", skill->name);
        printf("%s\n", (skill[i]).description);
        printf("%d\n", (skill[i]).of_def);
        printf("%d\n", (skill[i]).dmg_skll);
        printf("%s\n", (skill[i]).modifier);
        printf("%d, %d, %d\n", (skill[i]).stats_plyr[0], (skill[i]).stats_plyr[1], (skill[i]).stats_plyr[2]);
        i++;
    }
    fclose(fp); 
}

