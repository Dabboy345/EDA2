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

    
    /*char s[MAX_NAME];
    scanf("%s", e->name);
    e->stats[0]=5;
    e->stats[1]=10;
    e->stats[2]=150;
    for(int i=0; i<4;i++){get_skill(&e->skill[i], 50+i);}*/



    /*Scenario *scene = create_inizialize_Scenario();
    go_to_node_select_and_add(2,"scenario1.txt",scene);
    Decision temporary_checker;
    saveLastDecisionData(scene, &temporary_checker);
    int a;
    while(!is_terminal(&temporary_checker)){
        a= get_valid_input();
        break;
    }*/
    Enemy* e = (Enemy*)malloc(sizeof(Enemy));
    char line[] = "Seller: 5, 10, 150, 50, 51, 52, 53";
    put_enemy_info(line , e);
    combat(plyr, e, 20);

}

void save_game(){//Our save game function
    
}

void load_game(){//Our load game function
    
}

void exit_game(){//Our exit game function 
    
}

int main(){
    print_menu();//We will print the menu
    int a;
    scanf("%d", &a);//We will ask the user what option would he like to choose
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


