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


void put_enemy_info(char *line, Enemy *boss) {
    if (strcmp(line, "no enemy\n") == 0 || strcmp(line, "no enemy") == 0) {
        strcpy(boss->name, "None");
        for (int i = 0; i < 3; i++) {
            boss->stats[i] = 0;
        }
        for (int i = 0; i < MAX_SKILL; i++) {
            get_skill(&boss->skill[i], 100);
        }
        return;
    }

    char buffer[MAX_TXT]; // Create a copy of the string to manipulate by splitting the string
    int list_n_skills[4];
    strcpy(buffer, line);

    char *token = strtok(buffer, ":"); // Enemy name, strtok helps us to split the string
    if (token != NULL) {
        strcpy(boss->name, token);
    }

    // Get the stats
    for (int i = 0; i < 3; i++) {
        token = strtok(NULL, ",");
        if (token != NULL) {
            boss->stats[i] = atoi(token); // Conversion of char to int with atoi
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

void get_info_decision(Decision *choice, int node_number, char *filename_txt) {
    FILE *fp = fopen(filename_txt, "r");
    if (fp == NULL) {
        printf("Error opening the file\n");
        return;
    }
    int a;
    char buffer[MAX_TXT];
    while(!feof(fp)){
        fscanf(fp, "%dnode\n", &a);
        fgets(choice->option.description, MAX_TXT,fp);
        fgets(choice->option.pre_txt, MAX_TXT,fp);
        fgets(buffer, MAX_TXT,fp);
        put_enemy_info(buffer, &choice->option.enemy);
        fgets(choice->option.post_txt,MAX_TXT,fp);
        fgets(choice->option.option1,MAX_TXT,fp);
        fgets(choice->option.option2,MAX_TXT,fp);
        if(node_number == a){
            fclose(fp);
            return;
        }
    }
}


Decision *create_desicion(){
    Decision *new_decision = (Decision*)malloc(sizeof(Decision));
    if (new_decision == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    new_decision->next = NULL;
    return new_decision;
}

Scenario *create_inizialize_Scenario(){
    Scenario *scene = (Scenario*)malloc(sizeof(Scenario));
    scene->start = NULL;
    scene->end = NULL;
    return scene;
}


//Function to add a Decision to the Scenario
void addDecisionToScenario(Scenario *scenario, Decision *decision) { //Function to add a decion to the scenario
    if (scenario->start == NULL) {
        scenario->start = decision;
        scenario->end = decision;
    } else {
        scenario->end->next = decision;
        scenario->end = decision;
    }
    scenario->decisions_added++;
}

void *go_to_node_select_and_add(int node,char *filename,Scenario *scene){
    Decision *test = create_desicion();
    get_info_decision(test, node, filename);
    addDecisionToScenario(scene, test);
    print_decision(test);
}

void freeScenario(Scenario *scenario) { //Function to free the scenario
    Decision *current = scenario->start;
    Decision *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    scenario->start = NULL;
    scenario->end = NULL;
    scenario->decisions_added = 0;
}

void saveLastDecisionData(Scenario* scenario, Decision* tempDecision) {// Function to save the data of the last decision in the scenario linked list, this will be used for the function is terminal
    // Check if the scenario is valid and not empty
    if (scenario == NULL || scenario->start == NULL || tempDecision == NULL) {
        return;
    }

    // Initialize a pointer to traverse the list
    Decision* current = scenario->start;

    // Traverse the list until we reach the last node
    while (current->next != NULL) {
        current = current->next;
    }

    // Copy the data from the last decision to the temporary decision variable
    *tempDecision = *current;
}

int is_terminal(Decision *scene) { // This function will check if a node is an end node or not
    if (scene == NULL) { 
        return 0; // If the scene is NULL, it's not a valid end node
    }

    int a = strcmp(scene->option.option1, "- end node");
    int b = strcmp(scene->option.option2, "- end node");
    
    if (a == 0 && b == 0) {
        return 1; // The node is an end node the both options description is "- end node"
    } else {
        return 0; // The node is not an end node
    }
}



int get_valid_input() {
    int a;
    int valid = 0;

    while (!valid) { //if valid is 1 it is true and then the while will stop
        print_menu_option();
        printf("Your choice: ");
        
        if (scanf("%d", &a) != 1) {
            // Clear the invalid input
            while (getchar() != '\n'); // Discard invalid input until a newline is found
            printf("Invalid input. Please enter a number between 1 and 4.\n");
        } else if (a != 1 && a != 2 && a != 3 && a != 4) {
            printf("Please enter a valid option (1, 2, 3, or 4).\n");
        } else {
            valid = 1; // Valid input received
        }
    }

    return a;
}
