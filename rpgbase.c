#include "rpgbase.h"

void new_game(){//Our new game function
    Timestrike* stack = createTimestrike(50);//Initialize the stack for timestrike
    Skill *skill = (Skill*)calloc(MAX_NUMBER_SKILL_PLAYER, sizeof(Skill));
    //Get all the skills from the txt file of skills into an poineter of all the skills the player can choose
    if(skill == NULL){ 
        printf("Memory allocation failed\n");
        return;
    }
    for(int i =0; i<MAX_NUMBER_SKILL_PLAYER;i++){
        get_skill(&skill[i], i);
    }
    Character *plyr = create_character(skill);//Create the character

    //Scenario1
    if(run_game(1,"scenario1.txt",plyr, stack)==0){//Run game, if return 0, player exited the game
        return;
    }
    change_skill(skill, plyr);//Allow the player to change skills each time it completes a scenario (More gameplay)

    //Scenario2
    if(run_game(1,"scenario2.txt",plyr, stack)==0){
        return;
    }
    change_skill(skill, plyr);

    //Scenario3
    if(run_game(1,"scenario3.txt",plyr, stack)==0){
        return;
    }
    change_skill(skill, plyr);

    //Scenario4
    if(run_game(1,"scenario4.txt",plyr, stack)==0){
        return;
    }else{printf("\nYou won the game!!!!!!!!!!!!!\n");remove("auto_save.txt");free(stack);}
}

void load_game(char* buffer){//Our load game function
    Timestrike* stack = createTimestrike(50);//Initialize the stack for timestrike
    Skill *skill = (Skill*)calloc(MAX_NUMBER_SKILL_PLAYER, sizeof(Skill));
    //Get all the skills from the txt file of skills into an poineter of all the skills the player can choose
    Character *plyr = (Character*)malloc(sizeof(Character));//Initialize character
    if(skill == NULL){
        printf("Memory allocation failed\n");
        return;
    }
    for(int i =0; i<MAX_NUMBER_SKILL_PLAYER;i++){
        get_skill(&skill[i], i);
    }
    int* node_num = (int*)malloc(sizeof(int));//Create pointer to get the node number from the txt file
    int a = load_game_and_play(buffer, plyr, node_num);//Load information from a txt file
    //The function returns the scenario the player was on
    switch(a){
        case 1:
            //Scenario1
            if(run_game(*node_num,"scenario1.txt",plyr, stack)==0){//Run game, if return 0, player exited the game
                break;
            }
            *node_num = 1;//Reset node number to 1 to start the next scenario in the first node
            change_skill(skill, plyr);//Allow the player to change skills each time it completes a scenario (More gameplay)

        case 2:
            //Scenario2
            if(run_game(*node_num,"scenario2.txt",plyr, stack)==0){
                break;
            }
            *node_num = 1;
            change_skill(skill, plyr);

            
        case 3: 
            //Scenario3
            if(run_game(*node_num,"scenario3.txt",plyr, stack)==0){
                break;
            }
            *node_num = 1;
            change_skill(skill, plyr);
        
        case 4: 
            //Scenario4
            if(run_game(*node_num,"scenario4.txt",plyr, stack)==0){
                break;
            }else{printf("\nYou won the game!!!!!!!!!!!!!\n");remove("auto_save.txt");free(stack);}
    }   
}

int main(){
    int a = 0;
    while(a!=4){
        print_menu();//We will print the menu
        a = get_valid_input(1,4);//We will ask the user what option would he like to choose
        switch(a){
            case 1:
                new_game();//Start a new game
                break;
            case 2:
                load_game("auto_save.txt");//Load game from auto save
                break;
            case 3:
                char buffer[MAX_NAME];//Load game from a file previously saved
                printf("Please put the filename: ");
                scanf("%s", buffer);
                load_game(buffer);
                break;
            //If case is 4 nothing happens because it's the option to exit the game, so the program ends
        }
    }
    
}


