#include"rpg_base.h"
#include"rpg_game.c"

void new_game(){
    Skill skill[20] = (Skill*)malloc(sizeof(Skill));
    get_skill(skill);


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


