#include"rpg_base.h"

void new_game(){//Our new game function
    Skill *skill = (Skill*)calloc(20, sizeof(Skill));
    get_skill(skill);
    create_character(skill);

    //Decision* main_decision = decision[0];

}

void save_game(){//Our save game function
    
}

void load_game(){//Our load game function
    
}

void exit_game(){//Our exit game function 
    
}

int main(){
    print_menu();
    int a;
    fscanf("%d", &a);
    switch(a){
        case 1:
            new_game();
            break;
        case 2:
            save_game();
            break;
        case 3:
            load_game();
            break;
        case 4:
            exit_game();
            break;

    }
}


