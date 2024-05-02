#include"rpg_base.h"

void new_game(){
    Skill skill[20] = (Skill*)malloc(20*sizeof(Skill));
    get_skill(skill);
    create_character(skill);

}

void save_game(){
    
}

void load_game(){
    
}

void exit_game(){
    
}

int main(){
    print_menu();
    Skill *skill = (Skill*)malloc(sizeof(Skill));
    get_skill(skill);

}


