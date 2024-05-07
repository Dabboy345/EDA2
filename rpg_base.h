#include "common.h"
#include "rpg_game.h"

void print_menu(){//This will be the print function which will print the users menu
    printf("GAME LOGO\n");
    printf("PROSOMOÍOSI\n");
    printf("\n");
    printf("1. NEW GAME\n");
    printf("2. SAVE GAME\n");
    printf("3. Load GAME\n");
    printf("4. Exit GAME\n");
}


void print_logo();//We will use this funtion to print our logo

void print_game_name();//We will use this function to print the game name

void get_skill(Skill skill[]){
    FILE *fp;
    int i = 0;
    char c[MAX_NAME];
    fp = fopen("list_character-skill.txt", "r");
    while("SKILLS"!=fgets(c, MAX_NAME, fp)){;};
    while(!feof(fp)){
        fgets((skill[i]).name, MAX_NAME, fp);
        fgets((skill[i]).description, MAX_TXT, fp);
        fscanf(fp, "%d\n", &(skill[i]).of_def);
        fscanf(fp, "%d\n", &(skill[i]).dmg_skll);
        fgets((skill[i]).modifier, MAX_TXT, fp);
        fscanf(fp, "%d, %d, %d\n", &(skill[i]).stats_plyr[0], &(skill[i]).stats_plyr[1], &(skill[i]).stats_plyr[2]);
        
        /*printf("______%s\n", skill->name);
        printf("%s\n", (skill[i]).description);
        printf("%d\n", (skill[i]).of_def);
        printf("%d\n", (skill[i]).dmg_skll);
        printf("%s\n", (skill[i]).modifier);
        printf("%d, %d, %d\n", (skill[i]).stats_plyr[0], (skill[i]).stats_plyr[1], (skill[i]).stats_plyr[2]);
        */i++;
    }
    fclose(fp); 
}

