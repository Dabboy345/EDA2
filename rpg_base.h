#include "stdio.h"
#include "string.h"
#include "stdlib.h"
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

void print_menu(){
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

