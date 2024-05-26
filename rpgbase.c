#include "rpgbase.h"

void new_game(){//Our new game function
    Skill *skill = (Skill*)calloc(20, sizeof(Skill));
    if(skill == NULL){
        printf("Memory allocation failed\n");
        return;
    }
    for(int i =0; i<19;i++){
        get_skill(&skill[i], i);
    }

    Character *plyr = create_character(skill);

    //Scenario1
    run_game(1,"scenario1.txt", plyr);
    choose_skill(skill, plyr);

    //Scenario2
    //run_game(1,"scenario2.txt",plyr);
    //choose_skill(skill, plyr);

    //Scenario3
    run_game(1,"scenario3.txt",plyr);
    choose_skill(skill, plyr);

    //Scenario4
    //run game(1,"scenario4.txt",plyr);
    //choose_skill(skill, plyr);
  

}

void load_game(char* buffer){//Our load game function
    Skill *skill = (Skill*)calloc(20, sizeof(Skill));
    Character *plyr = (Character*)malloc(sizeof(Character));

    if(skill == NULL){
        printf("Memory allocation failed\n");
        return;
    }
    for(int i =0; i<19;i++){
        get_skill(&skill[i], i);
    }
    
    int* node_num = (int*)malloc(sizeof(int));
    int a = load_game_and_play(buffer, plyr, node_num);
    switch(a){
        case 1:
            //Scenario1
            if(run_game(*node_num,"scenario1.txt",plyr)==0){
                break;
            }
            *node_num = 1;
            choose_skill(skill, plyr);

        case 2:
            //Scenario2
            if(run_game(*node_num,"scenario2.txt",plyr)==0){
                break;
            }
            *node_num = 1;
            choose_skill(skill, plyr);

            
        case 3: 
            //Scenario3
            int run = run_game(*node_num,"scenario3.txt",plyr);
            if(run==0){
                break;
            }
            *node_num = 1;
            choose_skill(skill, plyr);
        
        case 4: 
            //Scenario4
            if(run_game(*node_num,"scenario4.txt",plyr)==0){
                break;
            }else{printf("\nYou won the game!!!!!!!!!!!!!\n");}
    }   
}

int main(){
    int a = 0;
    while(a!=4){
        print_menu();//We will print the menu
        a = get_valid_input(1,4);//We will ask the user what option would he like to choose
        switch(a){
            case 1:
                new_game();
                break;
            case 2:
                load_game("auto_save.txt");
                break;
            case 3:
                char buffer[MAX_NAME];
                printf("Please put the filename: ");
                scanf("%s", buffer);
                load_game(buffer);
                break;
        }
    }
    
}


