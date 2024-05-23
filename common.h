#ifndef _COMMON_H_
#define _COMMON_H_ // In this libary we have our data structures 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h> //Libary  with math functions
#include <ctype.h> //Libary that can convert Capital to small letter or vice versa, it can also check if something is alphabet, alphanemeric...etc. 
#include <stdbool.h> //Libary which enabels us to work with booleans

#define MAX_NAME 50 
#define MAX_TXT 350 
#define MAX_SKILL 4
#define MAX_DECISIONS 20

typedef struct { //Our data stucture for the skills
    char name[MAX_NAME];
    char description[MAX_TXT];
    int of_def; //1 for offensive, 0 for deffensive
    int dmg_skll;// 10-35
    char mod;
    int stats_plyr[3]; //dmg(0), def(1), hp(2)
    /*int dmg_plyr; 0-2       int def_plyr; 0 - 8       int hp_plyr; 25 - 50 */
    int skill_number;
} Skill;

typedef struct{ //This is our data structures for the character
    char name[MAX_NAME];
    int stats[3];//dmg(0), def(1), hp(2)
    //int dmg; 12 - 32      int def; 0 - 32       int hp; 100 - 200
    Skill skill[4];
}Character;

typedef struct{ //This is our data structures for the Enemy
    char name[MAX_NAME];
    int stats[3];//dmg(0), def(1), hp(2)
    Skill skill[4];
}Enemy;

typedef struct{
    char description[MAX_TXT];
    char pre_txt[MAX_TXT];
    Enemy enemy;
    char post_txt[MAX_TXT];
    char option1[MAX_TXT];
    char option2[MAX_TXT];
}Option;
//response text, narrative text (before battling the enemies), enemies (can be reused from other scenarios), 
//narrative text (after battling the enemies)

typedef struct{
    //char question_txt[MAX_TXT];
    Option option;
    struct Decision *next;
    int node_number;//This will help us to save the game 
}Decision;
//question text, options, number of options

typedef struct{
    Decision *start;
    Decision *end;
    int decisions_added;
}Scenario;

/*typedef struct{
    Character main;
    Decision last_descion;
}Save_game;*/

typedef struct{
    int max;
    int n;
    char chr;
    int temp;
}Mod;

#endif
