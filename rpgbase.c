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

    //Character *plyr = create_character(skill);

    /*Enemy* e = (Enemy*)malloc(sizeof(Enemy));
    char s[MAX_NAME];
    scanf("%s", e->name);
    //for(int i=0; i<3;i++){e->stats[i]=10;}
    e->stats[0]=5;
    e->stats[1]=10;
    e->stats[2]=150;
    for(int i=0; i<4;i++){get_skill(&e->skill[i], 50+i);}
    combat(plyr, e, 10);*/


    Scenario *scene = create_inizialize_Scenario();
    go_to_node_select_and_add(1,"scenario1.txt",scene);
    // while(!is_terminal()){
    //     scanf("")
    // }


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


