#include "common.h"
#include "rpg_game.h"
#include "prints.h"


void get_skill(Skill skill[]){
    FILE *fp;
    int i = 0;
    char c[MAX_NAME];
    fp = fopen("list_character_skill.txt", "r");
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

Node* get_node(int i1, int i2, Node* node){
    FILE *fp;
    int a = 0;
    int b = 0;
    fp = fopen("option.txt", "r");

    while (a!=i1 && b!=i2){fscanf(fp, "%d.%d\n", &a, &b);}
    while(!feof(fp)){
        //fgets((skill[i]).name, MAX_NAME, fp);
    fclose(fp); 
    } 
}

