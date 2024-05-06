#include"rpg_base.h"

void new_game(){
    Skill *skill = (Skill*)calloc(20, sizeof(Skill));
    get_skill(skill);
    create_character(skill);

    //Decision* main_decision = decision[0];

}

void save_game(){
    
}

void load_game(){
    
}

void exit_game(){
    
}

int main(){
    print_menu();
    new_game();

}


