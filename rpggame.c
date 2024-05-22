#include"rpggame.h"



void try_skill(Skill *skll){
    printf("---------------------------\n");
    printf("%s", skll->name);
    printf("---------------------------\n\n");
    printf("%s\n", skll->description);
    printf("Health points: %d\n", skll->stats_plyr[2]);
    for(int i = 0; i<skll->stats_plyr[2]; i++){printf("/");}
    printf("\n");
    printf("Defense: %d\n", skll->stats_plyr[1]);
    for(int i = 0; i<skll->stats_plyr[1]; i++){printf("/");}
    printf("\n");
    printf("Damage: %d\n", skll->stats_plyr[0]);
    for(int i = 0; i<skll->stats_plyr[0]; i++){printf("/");};
    printf("\n\n");
    if(skll->of_def==0){printf("It doesn't deal damage\n");}
    else if(skll->of_def==1){printf("%d damage dealt\n", skll->dmg_skll);};
    //print_mod(Skill* skill)
}

void get_skill(Skill *skill, int n){
    FILE *fp;
    char c[MAX_TXT];
    fp = fopen("list_character_skill.txt", "r");
    if (fp==NULL){
        printf("Error opening opening the file\n");
        fclose(fp);
        return;
    }
    int a;
    while(!feof(fp)){
        fscanf(fp, "%dskill\n", &a);
        fgets(skill->name, MAX_NAME, fp);
        fgets(skill->description, MAX_TXT, fp);
        fscanf(fp, "%d\n%d\n", &skill->of_def, &skill->dmg_skll);
        skill->mod = fgetc(fp);
        for(int i=0;i<3;i++){fscanf(fp, "%d,", &skill->stats_plyr[i]);}
        if(n==a){
            /*printf("\n");
            printf("_______________%s\n", skill->name);
            printf("%s\n", skill->description);
            printf("%d\n", skill->of_def);
            printf("%d\n", skill->dmg_skll);
            printf("%c\n", skill->mod);
            printf("%d, %d, %d\n", skill->stats_plyr[0], skill->stats_plyr[1], skill->stats_plyr[2]);*/
            
            fclose(fp); 
            return;
        }
    }
}

Character* create_character(Skill *skills){
    Character *player = (Character*)malloc(sizeof(Character));
    if(player == NULL){
        printf("Memory allocation failed\n");
        return NULL;
    }
    printf("Choose you character's name: ");
    scanf("%s", &player->name);
    //Choose skills

    //print all skills
    for(int i = 0; i<20; i++){
        printf("%d.%s",i+1, skills[i].name);
    }

    printf("\n");
    int temp=1;
    int test=0;
    while(temp!=0){
        printf("Type 0 to choose final skills\nTry a skill (1-20): ");
        test = scanf("%d", &temp);
        printf("\n");
        if((1<=temp) && (temp<=20)){
            try_skill(&(skills[temp-1]));
        }else if (test!=0){printf("Wrong input\n");}//When typing a letter it crashes
        
    }
   
    //create a function to try a skill "try_skill(skills[20], n)" n = number of skill
    //                                  description + test
    //...
    
    for(int i = 0; i<4; i++){
        printf("Choose a skill %d: ", i+1);
        scanf("%d", &temp); //We need to code so that the player can't have repeated skills
        player->skill[i] = skills[temp-1];
        printf(" %s\n", &(player->skill[i].name));

    }
    
    for(int i = 0; i<3; i++){
        temp = 0;
        for(int j = 0; j<4; j++){
            temp += player->skill[j].stats_plyr[i]; //With errors
        }
        player->stats[i] = temp;
    }
    return player;
}



/*void put_enemy_info(char *line, Enemy *boss) {
    if (strcmp(line, "no enemy") == 0) {
        for (int i = 0; i < MAX_SKILL; i++) {
            get_skill(&boss->skill[i], 100);  
        }
        return;
    }
    char buffer[MAX_TXT];//We create a copy of our string to manipulate by spliting the string
    int list_n_skills[4];
    strcpy(buffer, line);

    char *token = strtok(buffer, ":"); //Enemy name, strtoken helps us to split the string
    if (token != NULL) {
        strcpy(boss->name,token);
    }
    // Get the stats
    for (int i = 0; i < 3; i++) {
        token = strtok(NULL, ",");
        if (token != NULL) {
            boss->stats[i] = atoi(token); //Convesion of char to int with atoi 
        }
    }

    // Get the skill numbers
    for (int i = 0; i < MAX_SKILL; i++) {
        token = strtok(NULL, ",");
        if (token != NULL) {
            list_n_skills[i] = atoi(token);
            get_skill(&boss->skill[i], list_n_skills[i]);
        }
    }
}


void get_info(Node *root, int a){
    FILE *fp = fopen("scenario.txt", "r");
    if (fp == NULL) {
        printf("Cannot open the file\n");
        return;
    }
    int current_section = 0;
    char line[MAX_TXT];
    // Loop until we find the desired section
    while (fgets(line, MAX_TXT, fp)) {
        if (isdigit(line[0])) {
            sscanf(line, "%d.", &current_section);
            if (current_section == a) {
                break;
            }
        }
    }
    // If the desired section wasn't found
    if (current_section != a) {
        printf("Section %d not found\n", a);
        fclose(fp);
        return;
    }
    // Read the necessary lines from the file
    fgets(root->option.description, MAX_TXT, fp);
    fgets(root->option.pre_txt, MAX_TXT, fp);
    
    fgets(line, MAX_TXT, fp);
    put_enemy_info(line, &root->option.enemy);

    fgets(root->option.post_txt, MAX_TXT, fp);
    fgets(root->descions.question_txt, MAX_TXT, fp);
    fgets(root->descions.option[0].description, MAX_TXT, fp);
    fgets(root->descions.option[1].description, MAX_TXT, fp);

    fclose(fp);
}


Scenario *create_ini_scenario() {
    Scenario *scene = (Scenario*)malloc(sizeof(Scenario));
    if (scene == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    scene->start = (Node*)malloc(sizeof(Node));
    if (scene->start == NULL) {
        printf("Memory allocation failed\n");
        free(scene);
        return NULL;
    }
    scene->start->next = NULL;
    scene->end = scene->start;
    return scene;
}

void free_node(Node *node) {
    if (node != NULL) {
        free(node);
    }
}

void free_scenario(Scenario *scene) {
    if (scene == NULL) {
        return;
    }

    Node *current = scene->start;
    Node *next;

    // Traverse the linked list and free each node
    while (current != NULL) {
        next = current->next;
        free_node(current);
        current = next;
    }

    // Free the Scenario structure itself
    free(scene);
} */


