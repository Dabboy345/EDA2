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
    if(skll->of_def==0){printf("It doesn't deal damage\n\n");}
    else if(skll->of_def==1){printf("%d damage dealt\n\n", skll->dmg_skll);};
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
        skill->mod.chr = fgetc(fp);
        for(int i=0;i<3;i++){fscanf(fp, "%d,", &skill->stats_plyr[i]);}
        if(n==a){
            skill->skill_number = a;
            skill->mod.temp = 0;
            skill->mod.n = 0;
            switch(skill->mod.chr){
                case 'h':
                    skill->mod.max = 2;
                    break;
                case 'd':
                    skill->mod.max = 1;
                    break;
                case 'v':
                    skill->mod.max = 2;
                    break;
                case 's':
                    skill->mod.max = 1;
                    break;
                case 'r':
                    skill->mod.max = 3;
                    break;
            }

            /*printf("\n");
            printf("_______________%s\n", skill->name);
            printf("%s\n", skill->description);
            printf("%d\n", skill->of_def);
            printf("%d\n", skill->dmg_skll);
            printf("%c\n", skill->mod.chr);
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
    printf("\n");
    for(int i = 0; i<20; i++){
        printf("%d.%s",i+1, skills[i].name);
    }

    printf("\n");
    int temp=1;
    int test=0;
    while(temp!=0){
        printf("\nType 0 to choose final skills\nTry a skill (1-20): ");
        printf("\n");
        temp = get_valid_input(0, 20);
        if(0!=temp){try_skill(&(skills[temp-1]));}
        
    }
    
    for(int i = 0; i<4; i++){
        printf("Choose skill %d: ", i+1);
        temp = get_valid_input(1, 20); //We need to code so that the player can't have repeated skills
        //for(int j = 0;j<i;i++){}
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
            choice->node_number = node_number;
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

void go_to_node_select_and_add(int node,char *filename,Scenario *scene, Character* plyr){
    Decision *test = create_desicion();
    get_info_decision(test, node, filename);
    addDecisionToScenario(scene, test);
    print_decision(test, plyr);
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
        printf("NULL");
        return 0; // If the scene is NULL, it's not a valid end node
    }

    int a = (scene->option.option1[2]=='E' && scene->option.option1[6]=='n')? 0:1;
    int b = (scene->option.option2[2]=='E' && scene->option.option2[6]=='n')? 0:1;
    
    if (a == 0 && b == 0) {
        return 1; // The node is an end node the both options description is "- end node"
    } else {
        return 0; // The node is not an end node
    }
}



int get_valid_input(int first, int size) {
    int a;
    int valid = 0;

    while (!valid) { //if valid is 1 it is true and then the while will stop        
        if (scanf("%d", &a) != 1) {
            // Clear the invalid input
            while (getchar() != '\n'); // Discard invalid input until a newline is found
            printf("\n----> Invalid input. Please enter a number between %d and %d\n\n", first, size);
        } else if (a < first || a > size) {
            printf("\n----> Invalid input. Please enter a number between %d and %d\n\n", first, size);
        } else {
            valid = 1; // Valid input received
        }
    }

    return a;
}

int get_last_node_numeber(Scenario *scenario) {
    if (scenario == NULL || scenario->start == NULL) {
        return -1; // Indicate error if the scenario is NULL or empty
    }

    Decision *current = scenario->start; //Traverse the list until we find the last node
    while (current->next != NULL) {
        current = current->next;
    }

    return current->node_number;//Return the node number
}


void save_game(Scenario *scene, Character *character, char *filename){
    char buffer[MAX_NAME]; //to save the name of the file
    //Decision lastdescion;
    printf("Write the file name (finishing with .txt): ");
    scanf("%s", buffer);
    FILE *fp;
    fp = fopen(buffer,"w");
    if (fp==NULL){
        printf("Error saving the file\n");
        return;
    }   
    fprintf(fp,"%s\n",character->name);
    for(int i=0; i<3;i++){
        fprintf(fp, "%d\n", character->stats[i]); //We save the stat that player had
    }
    for(int i=0;i<4;i++){
        fprintf(fp, "%d\n", character->skill[i].skill_number); //We save the skill numbers
    }
    int a = get_last_node_numeber(scene);
    if( a != -1){
        fprintf(fp, "%d\n", a);
        printf("File Saved Sucesfully\n");
        fprintf("%s\n",filename);
        fclose(fp);
        return;
    }
    else {
        printf("Error saving the file\n");
        fclose(fp);
        return;
    }

}


void run_game(int node_number, char *filename){
    Skill *skill = (Skill*)calloc(20, sizeof(Skill));
    if(skill == NULL){
        printf("Memory allocation failed\n");
        return;
    }
    for(int i =0; i<19;i++){
        get_skill(&skill[i], i);
    }

    Character *plyr = create_character(skill);


    Scenario *scene = create_inizialize_Scenario();
    go_to_node_select_and_add(node_number,filename,scene, plyr);
    Decision temporary_checker;
    saveLastDecisionData(scene, &temporary_checker);
    int a;
    int option_selected;
    do{
        print_menu_option();
        printf("Your choice: ");
        a= get_valid_input(1, 4);
        printf("\n");
        switch(a){
            case 1:
                option_selected = (temporary_checker.node_number) *2;
                go_to_node_select_and_add(option_selected,"scenario1.txt",scene, plyr);
                saveLastDecisionData(scene, &temporary_checker);
                break;
            case 2:
                option_selected = ((temporary_checker.node_number) *2)+1;
                go_to_node_select_and_add(option_selected,"scenario1.txt",scene, plyr);
                saveLastDecisionData(scene, &temporary_checker);
                break;
            case 3:
                save_game(scene, plyr);
                break;
            case 4:
                goto exit;
                break;

        }
        printf("\n_____________________________________________________\n");
    }while(is_terminal(&temporary_checker)==0);
    //printf("You have the scenario\n");
    exit:
    //printf("Thanks for playing our game\n");
    freeScenario(scene);
    free(plyr);
    free(skill);
}


void load_game_and_play(){

    Scenario *scene = create_inizialize_Scenario();
    Character *plyr = (Character*)malloc(sizeof(Character));

    char buffer[MAX_NAME];
    printf("Please put the filename with .txt: ");
    scanf("%s",buffer);

    FILE *fp = fopen(buffer,"r");
    if (fp==NULL){
        printf("Error loading the file information or file doesn't exist\n");
        return;
    }
    fscanf(fp, "%s\n", plyr->name);//We get the saved name
    for (int i = 0; i < 3; i++) { //We put the character stats
        fscanf(fp, "%d\n", &plyr->stats[i]);
    }

    int skill_number;//Skill number
    for (int i = 0; i < 4; i++) {
        fscanf(fp, "%d\n", &skill_number);
        get_skill(&plyr->skill[i], skill_number);
    }

    int last_node_number;
    fscanf(fp, "%d\n", &last_node_number);
    fclose(fp);

    printf("Game loaded successfully. Starting from node %d...\n", last_node_number);
    printf("Starting to play\n");

    // run game function
    /*
    go_to_node_select_and_add(last_node_number,"scenario1.txt",scene, plyr);
    Decision temporary_checker;
    saveLastDecisionData(scene, &temporary_checker);
    int a;
    int option_selected;
    do{
        print_menu_option();
        printf("Your choice: ");
        a= get_valid_input(1, 4);
        printf("\n");
        switch(a){
            case 1:
                option_selected = (temporary_checker.node_number) *2;
                go_to_node_select_and_add(option_selected,"scenario1.txt",scene, plyr);
                saveLastDecisionData(scene, &temporary_checker);
                break;
            case 2:
                option_selected = ((temporary_checker.node_number) *2)+1;
                go_to_node_select_and_add(option_selected,"scenario1.txt",scene, plyr);
                saveLastDecisionData(scene, &temporary_checker);
                break;
            case 3:
                save_game(scene, plyr);
                break;
            case 4:
                goto exit;
                break;

        }
        printf("\n_____________________________________________________\n");
    }while(is_terminal(&temporary_checker)==0);
    printf("You have the scenario\n");
    exit:
    printf("Thanks for playing our game\n");
    freeScenario(scene);
    free(plyr);*/
    


}

// order skills
// Utility function to swap two Skill structures
void swap(Skill* p1, Skill* p2) {
    Skill temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

// Partition function for quicksort
int partition(Skill arr[], int low, int high) {
    // Choose the pivot as the damage value of the high element
    int pivot = arr[high].dmg_skll;
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        // If the current element's damage is greater than the pivot
        if (arr[j].dmg_skll > pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Quicksort function for Skill array
void quickSort(Skill arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Function to read skills from a file and sort them by damage
void order_skills_dmg() {
    // Open the file
    FILE *fp = fopen("list_character_skill.txt", "r");
    if (fp == NULL) {
        printf("Error opening the file\n");
        return;
    }

    // Read skills into an array
    Skill skills[100]; // Assume there are at most 100 skills
    int count = 0;

    while (!feof(fp) && count < 100) {
        fscanf(fp, "%*dskill\n"); // Skip skill number in the file
        fgets(skills[count].name, MAX_NAME, fp);
        fgets(skills[count].description, MAX_TXT, fp);
        fscanf(fp, "%d\n%d\n", &skills[count].of_def, &skills[count].dmg_skll);
        skills[count].mod.chr = fgetc(fp);
        for (int i = 0; i < 3; i++) {
            fscanf(fp, "%d,", &skills[count].stats_plyr[i]);
        }
        fgetc(fp); // To consume the newline character
        count++;
    }
    fclose(fp);

    // Sort the skills by damage
    quickSort(skills, 0, count - 1);

    // Print sorted skills
    printf("Sorted skills by damage:\n");
    for (int i = 0; i < count; i++) {
        printf("Name: %s", skills[i].name);
        printf("Description: %s", skills[i].description);
        printf("Damage: %d\n", skills[i].dmg_skll);
        printf("---------------------------\n");
    }
}

/*int main() {
    order_skills_dmg();
    return 0;
}*/
