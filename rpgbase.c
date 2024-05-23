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


    Scenario *scene = create_inizialize_Scenario();
    go_to_node_select_and_add(1,"scenario1.txt",scene, plyr);
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
    printf("Thanks for playing our game\n");
    freeScenario(scene);
}

void load_game(){//Our load game function
    load_game_and_play();
}

int main(){
    int a = 0;
    while(a!=3){
        print_menu();//We will print the menu
        a = get_valid_input(1,3);//We will ask the user what option would he like to choose
        switch(a){
            case 1:
                new_game();
                break;
            case 2:
                load_game();
                break;
        }
    }
    
}


