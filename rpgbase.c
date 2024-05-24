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

    run_game(1,"scenario1.txt", plyr);
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


