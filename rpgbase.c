#include "rpgbase.h"

void new_game(){//Our new game function
    Skill *skill = (Skill*)calloc(20, sizeof(Skill));
    /*for(int i =0; i<18;i++){
        get_skill(&skill[i], i);
    }*/
    get_skill(&skill[0], 1);
    
    //create_character(skill);
    //Decision* main_decision = decision[0];

    /*This is an example of the implatiaion of what we would like to do, we will create/add functions necessary to make it more automatic
    Node *root = create_node();
    add_Node_left(root);
    add_Node_right(root);
    FILE *c = fopen("desicion.txt","r");
    fgets(root->descions.question_txt, MAX_TXT, c);//This will get your descriptions of where we are
    fgets(root->descions.option[0], MAX_TXT, c);//Our first options 
    fgets(root->descions.option[1], MAX_TXT, c);//Our second options 
    //Now here we will print the options and make the player chose it after the selection we will go to the diffreent node 
    //and repeat the same process to play the game

    //Things needed to do this part function to print the despcription,options.. part of each node and function to set the selected
    //node by the user and take the necessary infotmation from the corresponding txt file.*/ 

    //Imporatant things to take into account error handaling, free the memory created dnamically for each node(create this function)
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


