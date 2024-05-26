#include"rpggame.h"

void print_mod(Skill* skll){
    switch(skll->mod.chr){
        case 'h':
            printf("It heals you %d hp\n\n", skll->dmg_skll);
            break;
        case 'd':
            printf("It adds %d defense\n\n", skll->dmg_skll);
            break;
        case 'v':
            printf("It deals some extra damage (depends on the character's attack) during 3 turns\n\n");
            break;
        case 's':
            printf("It  stuns the opponent, not allowing them to attack next turn\n\n");
            break;
        case 'r':
            printf("It takes 1 turn to charge it and another one to use it\n\n");
            break;
        case 'f':
            printf("It increases the general damage (depends on the character's attack)\n\n");
            break;
        case 'p':
            printf("It gives you a %d %% chance of dodging the next attack\n\n", skll->dmg_skll*3);
            break;
    }
}


void try_skill(Skill *skll){
    printf("\n---------------------------\n");
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
    else if(skll->of_def==1){printf("It deals %d damage\n\n", skll->dmg_skll);};
    print_mod(skll);
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
                    skill->mod.max = 4;
                    break;
                case 'f':
                    skill->mod.max = 3;
                    break;
                case 'p':
                    skill->mod.max = 4;
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

void choose_skill(Skill *skills, Character *player){
    for(int i = 0; i<20; i++){
        printf("%d.%s",i+1, skills[i].name);
    }

    printf("\n");
    int temp=1;
    int test=0;
    while(temp!=0){
        printf("\nType 0 to choose final skills\nTry a skill (1-20): ");
        temp = get_valid_input(0, 20);
        printf("\n");
        if(0!=temp){try_skill(&(skills[temp-1]));}
    }
    
    for(int i = 0; i<4; i++){
        repeated_skill:
        printf("Choose skill %d: ", i+1);
        temp = get_valid_input(1, 20); //We need to code so that the player can't have repeated skills
        //for(int j = 0;j<i;i++){}
        for(int j=0;j<i;j++){if(player->skill[j].skill_number==temp-1){
            printf("\nYou can't have %stwice\n\n", player->skill[j].name);goto repeated_skill;}}
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
}

Character* create_character(Skill *skills){
    Character *player = (Character*)malloc(sizeof(Character));
    if(player == NULL){
        printf("Memory allocation failed\n");
        return NULL;
    }
    printf("Choose you character's name (no spaces): ");
    scanf("%s", &player->name);
    for(int i=0;i<strlen(player->name);i++){rand();}//More random factor
    while (getchar() != '\n');
    printf("\n");
    choose_skill(skills, player);
    printf("\n\nFinal character:\n%s\n\n", player->name);

    printf("Health points: %d\n", player->stats[2]);
    for(int i = 0; i<player->stats[2]; i++){printf("|");}
    printf("\n");
    printf("Defense: %d\n", player->stats[1]);
    for(int i = 0; i<player->stats[1]; i++){printf("]");}
    printf("\n");
    printf("Damage: %d\n", player->stats[0]);
    for(int i = 0; i<player->stats[0]; i++){printf("}");};
    printf("\n\n");   
    return player;
}


void put_enemy_info(char *line, Enemy *boss) { //Function to helps us put the enemy info, we recive as parameter a line from the txt and a enemy where to save the information recived 
    if (strcmp(line, "no enemy\n") == 0 || strcmp(line, "no enemy") == 0) { //If there is not an enemy then we put None to name 
        strcpy(boss->name, "None");
        for (int i = 0; i < 3; i++) { //We put the stats to 0
            boss->stats[i] = 0;
        }
        for (int i = 0; i < MAX_SKILL; i++) {
            get_skill(&boss->skill[i], 100); //in the list_character skill the skill 100 is for the when ther is no enemy
        }
        return;
    }
    //If there is an enemy 
    char buffer[MAX_TXT]; // Create a buffer to manipulate the give line
    int list_n_skills[4]; //We create a temporary array to save the number of skills
    strcpy(buffer, line); //We copy the given line into the buffer
    //Strtok is a function provided by string.h which helps us mapulate string
    char *token = strtok(buffer, ":"); // We separate the string until its name and put it ot the enemy name
    if (token != NULL) {
        strcpy(boss->name, token);
    }

    // Get the skill numbers
    for (int i = 0; i < MAX_SKILL; i++) { //We do the same thing as we did before to get the information about the skills
        token = strtok(NULL, ",");
        if (token != NULL) {
            list_n_skills[i] = atoi(token);
            get_skill(&boss->skill[i], list_n_skills[i]); //We use the function get skill to get the information about the skills
        }
    }
}

void get_info_decision(Decision *choice, int node_number, char *filename_txt) { //Function to helps us to put the the info for a decision
    FILE *fp = fopen(filename_txt, "r"); //We open the file which we want to read the information from
    if (fp == NULL) { //Error Handeling 
        printf("Error opening the file\n");
        return;
    }
    int a; //Create a temporary varable to check if the if the number is same as the node_number 
    char buffer[MAX_TXT]; //To put the line of enenmy and pass it to the function put enemy info
    while(!feof(fp)){ //We repeat this process until we haven't reached the End of file
        fscanf(fp, "%dnode\n", &a); //We get the node number and save it to the a 
        fgets(choice->option.description, MAX_TXT,fp); //We get the description
        fgets(choice->option.pre_txt, MAX_TXT,fp); //We get the pre text
        fgets(buffer, MAX_TXT,fp); //We get the line which has the information about the enemy
        put_enemy_info(buffer, &choice->option.enemy);// we pass the inforamtion about the enemy to the functio we programmed before
        fgets(choice->option.post_txt,MAX_TXT,fp); //We get the post text 
        fgets(choice->option.option1,MAX_TXT,fp); //We get the desciption of option one and option 2 
        fgets(choice->option.option2,MAX_TXT,fp);
        if(node_number == a){ //We check if the if the a is same as the node number
            choice->node_number = node_number; //if it then we updrage the choice node number
            fclose(fp); //And we close the file 
            return;
        }
    }
}


Decision *create_desicion(){//Funciton which helps us allocate memory dynamically and inizilate  a decision 
    Decision *new_decision = (Decision*)malloc(sizeof(Decision));
    if (new_decision == NULL) { //Error Handeling 
        printf("Memory allocation failed\n");
        return NULL;
    }
    new_decision->next = NULL; //We put the created decision pointer null because at the moment it isn't pointing at anything 
    return new_decision;
}

Scenario *create_inizialize_Scenario(){ //Function to allocate memory and iniziale a scenario link list 
    Scenario *scene = (Scenario*)malloc(sizeof(Scenario)); // We do a malloc 
    if(scene == NULL){ //Error hadeling
        printf("Memory allocation failed\n");
    }
    scene->start = NULL; //We put both of the pointer to null because at the beginging we don't have anything
    scene->end = NULL;
    return scene;
}



void addDecisionToScenario(Scenario *scenario, Decision *decision) { //Function to add a decion to the scenario
    if (scenario->start == NULL) { //If the node recived is first in the list then we put it as the first and last node 
        scenario->start = decision;
        scenario->end = decision;
    } else {
        scenario->end->next = decision; //We move the pointer of the end->next to the decision 
        scenario->end = decision; //We say that the decision is the end 
    }
    scenario->decisions_added++; //We increemt the number of decision added to the list 
}

void go_to_node_select_and_add(int node,char *filename,Scenario *scene, Character* plyr){ 
    Decision *test = create_desicion();
    get_info_decision(test, node, filename);
    addDecisionToScenario(scene, test);
    save_game(scene, plyr, "auto_save.txt");
    print_decision(test, plyr);
} //This function helps us create a desicion, get the information, add it to the the link list and print its information

void freeScenario(Scenario *scenario) { //Function to free the scenario
    Decision *current = scenario->start; //We create a temporary pointer and point at the start 
    Decision *next;

    while (current != NULL) { //We go by freeing node by node 
        next = current->next; //We save the save the next of the current pointer 
        free(current); //We free the current 
        current = next; // And we say that the current one is the next we saved and we repat this process until the end 
    }

    scenario->start = NULL; //After freeing all the nodes we put the pointers to null
    scenario->end = NULL;
    scenario->decisions_added = 0; //By freeing we remove the nodes so we put it ot 0
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


void save_game(Scenario *scene, Character *character, char* buffer){
    FILE *fp;
    fp = fopen(buffer,"w"); //We open a file poiner in the wirting mode 
    if (fp==NULL){ //Error Handeling 
        printf("Error saving the file\n");
        return;
    }   
    fprintf(fp,"%s\n",character->name); //We print the character name into the file 
    for(int i=0; i<3;i++){
        fprintf(fp, "%d\n", character->stats[i]); //We save the stat that player had
    }
    for(int i=0;i<4;i++){
        fprintf(fp, "%d\n", character->skill[i].skill_number); //We save the skill numbers
    }
    int a = get_last_node_numeber(scene);
    if( a != -1){ //If it is different than -1 means that ther is no error getting the last number
        fprintf(fp, "%d\n", a); //We save the last decion node numeber he played 
        fprintf(fp, "%s\n", scene->filename); //We print in which scenario we were situated 
        printf("Game saved\n");
        fclose(fp); //We close the file 
        return;
    }
    else {
        printf("Error saving the file\n");
        fclose(fp);
        return;
    }

}


int run_game(int node_number, char *filename, Character *plyr){
    Scenario *scene = create_inizialize_Scenario();
    strcpy(scene->filename,filename);
    go_to_node_select_and_add(node_number,scene->filename,scene, plyr);
    Decision temporary_checker;
    saveLastDecisionData(scene, &temporary_checker);
    int a;
    int option_selected;
    char* buffer;
    do{
        print_menu_option();
        printf("Your choice: ");
        a= get_valid_input(1, 4);
        printf("\n");
        switch(a){
            case 1:

                option_selected = (temporary_checker.node_number) *2;
                go_to_node_select_and_add(option_selected,scene->filename,scene, plyr);
                saveLastDecisionData(scene, &temporary_checker);
                break;
            case 2:
                option_selected = ((temporary_checker.node_number) *2)+1;
                go_to_node_select_and_add(option_selected,scene->filename,scene, plyr);
                saveLastDecisionData(scene, &temporary_checker);
                break;
            case 3:
                printf("Write the file name(with txt): "); //We ask the user to what would he like teh file to be called 
                scanf("%s", buffer);
                save_game(scene, plyr, buffer);
                break;
            case 4:
                return 0;
                break;

        }
        printf("________________________________________________________________________________\n\n");
    }while(is_terminal(&temporary_checker)==0);
    //printf("You have the scenario\n");
    //printf("Thanks for playing our game\n");
    freeScenario(scene);
    return 1;
    //free(plyr);
}
 

int load_game_and_play(char *buffer, Character* plyr, int* last_node_number){
    int number_scenario;//To know in which scenario we are 
    Scenario *scene = create_inizialize_Scenario();

    FILE *fp = fopen(buffer,"r");
    if (fp==NULL){
        printf("Error loading the file information or file doesn't exist\n");
        return 0; //It means that there is error loading the information
    }
    fscanf(fp, "%s\n", plyr->name);//We get the saved name
    for (int i = 0; i < 3; i++) { //We put the character stats
        fscanf(fp, "%d\n", &plyr->stats[i]);
    }

    int skill_number;//Skill number
    for (int i = 0; i < 4; i++) {
        fscanf(fp, "%d\n", &skill_number);
        get_skill(&plyr->skill[i], skill_number);//We put the skills
    }

    fscanf(fp, "%d\n", last_node_number);//We get the node played
    fscanf(fp,"%s\n",scene->filename );
    fclose(fp);

    printf("Game loaded successfully. Starting from node %d...\n", *last_node_number);
    printf("Starting to play\n\n. . .\n\n");

    //run_game(last_node_number,scene->filename, plyr);

    if(scene->filename[8]=='1'){
        number_scenario = 1;
    }

    else if(scene->filename[8]=='2'){
        number_scenario = 2;
    }

    else if(scene->filename[8]=='3'){
        number_scenario = 3;
    }

    else if(scene->filename[8]=='4'){
        number_scenario = 4;
    }
    return number_scenario;

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


//Functions related with dictionary
/*
long int hash_function(char *skill_name){
    int name_skill_size = strlen(skill_name);
    int addition_ascii_value = 0;
    for(int i =0; i<name_skill_size; i++){
        addition_ascii_value += (int)skill_name[i]; //This int insisde paraentesis helps us to get Ascii value of each character
    }
    
    return addition_ascii_value % MAX_DICTONARY_SIZE;
}

void create_inizialize_dic(int size){
    Skill_usuage_dicionary *dicionary = (Skill_usuage_dicionary*)malloc(sizeof(Skill_usuage_dicionary));
    dicionary->size_dicionary = size;
    dicionary->hashmap= (dic_element*)calloc(size,sizeof(dic_element));
    for (int i = 0; i < MAX_DICTONARY_SIZE; i++) {
        dicionary->hashmap[i].isempty = true;
    }
    dicionary->skills_added = 0;
}

void insert_skill (Skill_usuage_dicionary *dic, Skill skill){
    long int index = hash_function(skill.name); //We do the hash function of the skill name
    dic_element *new_element = (dic_element*)malloc(sizeof(dic_element)); //We create a new element 
    strcpy(new_element->key,skill.name);//We put the key as the item
    new_element->skill = skill; //We put the skill info in the dictionary
    new_element->usage_counter = 0; //When we put it to the dictionary it will have 0 usage
    while(dic->hashmap[index] != true){
        index++;
    }

}

*/