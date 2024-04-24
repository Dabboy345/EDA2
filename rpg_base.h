#include "stdio.h"
#define MAX_NAME 30 
#define MAX_TXT 200 

typedef struct{
    char name[MAX_NAME];
    char description[MAX_TXT];
    int of_def; //1 for offensive, 0 for deffensive
    int dmg_skll;
    int modifier;
    int dmg_plyr; //3 - 8
    int def_plyr; //0 - 8
    int hp_plyr; //25 - 50
}Skill;
