#include"rpg_base.h"
int main(){
    print_menu();
    Skill *skill = (Skill*)malloc(sizeof(Skill));
    get_skill(skill);
}


