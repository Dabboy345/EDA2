#include"rpggame.h"



void try_skill(Skill *skll){
    printf("_- %s -_\n", skll->name);
    printf("Health points: %d\n", skll->stats_plyr[2]);
    for(int i = 0; i<skll->stats_plyr[2]; i++){printf("/");}
    printf("\n");
    printf("Defense: %d\n", skll->stats_plyr[1]);
    for(int i = 0; i<skll->stats_plyr[1]; i++){printf("/");}
    printf("\n");
    printf("Damage: %d\n", skll->stats_plyr[0]);
    for(int i = 0; i<skll->stats_plyr[0]; i++){printf("/");};
    printf("\n");
    if(skll->of_def==0){printf("%d def or heal?\n", skll->dmg_skll);}
    else if(skll->of_def==1){printf("%d damage dealt\n", skll->dmg_skll);};
    printf("It has %s modifier\n", skll->modifier);
}

void get_skill(Skill *skill, int n){
    FILE *fp;
    int i = 0;
    char c[MAX_NAME];
    fp = fopen("list_character_skill.txt", "r");
    int a;
    while(!feof(fp)){
        if(a==n && 1==fscanf(fp,"%dskill\n", &a)){
            long line = ftell(fp);
            fseek(fp, line, SEEK_SET);
            break;
        }
        getc(fp);
    }
    fgets(skill->name, MAX_NAME, fp);
    fgets(skill->description, MAX_TXT, fp);
    fscanf(fp, "%d\n%d\n", &skill->of_def, &skill->dmg_skll);
    //fscanf(fp, "%d\n", &skill->dmg_skll);
    fgets(skill->modifier, MAX_NAME, fp);
    for(int i=0;i<3;i++){fscanf(fp, "%d,", &skill->stats_plyr[i]);}
    //fscanf(fp, "%d,%d,%d\n", &skill->stats_plyr[0], skill->stats_plyr[1], &skill->stats_plyr[2]);

    printf("\n");
    printf("_______________%s\n", skill->name);
    printf("%s\n", skill->description);
    printf("%d\n", skill->of_def);
    printf("%d\n", skill->dmg_skll);
    printf("%s\n", skill->modifier);
    printf("%d, %d, %d\n", skill->stats_plyr[0], skill->stats_plyr[1], skill->stats_plyr[2]);
    
    fclose(fp); 
}

Character* create_character(Skill *skills){
    Character *player = (Character*)malloc(sizeof(Character));
    printf("Choose you character's name: ");
    scanf("%s", &player->name);
    //Choose skills

    //print all skills
    for(int i = 0; i<20; i++){
        printf("%d.-%s",i+1, skills[i].name);
    }

    printf("\n");
    int temp=1;
    int test=0;
    while(temp!=0){
        printf("Try a skill (1-20): ");
        test = scanf("%d", &temp);
        if((test!=0)&&(1<=temp) && (temp<=20)){
            try_skill(&(skills[temp]));
        }else{printf("Wrong input\n");}//When typing a letter it crashes
        
    }
   
    //create a function to try a skill "try_skill(skills[20], n)" n = number of skill
    //                                  description + test
    //...
    
    for(int i = 0; i<4; i++){
        printf("Choose a skill %d: ", i+1);
        scanf("%d", &temp); //We need to code so that the player can't have repeated skills
        player->skill[i] = skills[temp-1];
        printf(" %s\n", &(player->skill[i].name));

    }
    
    for(int i = 0; i<3; i++){
        temp = 0;
        for(int j = 0; j<4; j++){
            temp += player->skill[j].stats_plyr[i]; //With errors
        }
        player->stats[i] = temp;
    }
    return player;
}



void combat(Character *plyr, Enemy *enmy, int size){
    Queue* q = init_queue();
    for(int i = 0; i<size; i++){
        q = enqueue(q, *plyr, *enmy);
    }
    


    int rand_n = rand();
        if(rand_n%2 == 0){
            int a;
            for(int j = 0; j<4; j++){printf("%d - %s\n",j+1, plyr->skill[j]);}
            printf("Choose skill: ");
            scanf("%d", &a);

        }

}


// Node* get_node(int i, Node* node){
//     FILE *fp;
//     int a = 0;
//     fp = fopen("option.txt", "r");

//     while (a!=i){fscanf(fp,"%d.%d\n",&a);}
//     while(!feof(fp)){
//         //fgets((skill[i]).name, MAX_NAME, fp);
//     fclose(fp); 
//     } 
// }



Node *create_node(){//This function will create us a tree
    Node *root = (Node*)malloc(sizeof(Node));
    root->left = NULL;
    root->right = NULL;
    return root;
}

void add_Node_right( Node *root/*We could other valrable*/){ //This function enables to add new node to our tree
    Node *new = create_node();
    root->right = new;
}

void add_Node_left(Node *root){
    Node *new =  create_node();
    root->left = new;
}

Enemy *put_the_enemy(char const *a){//it will recive a line which is not modificable 
    if((a[0]=='n')&&(a[1]=='o')){
        return ; //It means that we have no enemy
    }

    Enemy *temp = (Enemy*)malloc(sizeof(Enemy));//We create a local variable 
    if (temp = NULL){
        printf("memory allocation failed/n");//The malloc failed
        return;
    }
    //fscanf("")
    return temp; //Aqui tambien tendriamos q hacer una funcion q recibendo el nombre de skill ya ponga los valores q toca
}


void get_info(Node *root,int a ){//the integer represent what is the information we want and in which node we want it to put 
    FILE *fp = fopen("scenario.txt","r");
    if(fp==NULL){ //Error handeling 
        printf("Error openning the file /n");
        fclose(fp);
    } 

    //char buffer[MAX_TXT];//We will use this temp variable to save the description


    //We get the description
    // fscanf(fp, "%d.- %s", buffer);
    // strcpy(buffer,root->option.description);
    fgets(root->option.description, MAX_TXT, fp);

    // //We get the pre_text
    // fgets(buffer, MAX_TXT, fp);
    // strcpy(buffer,root->option.pre_txt);
    fgets(root->option.pre_txt, MAX_TXT, fp);

    // //We get the enemy information
    // fgets(buffer, MAX_TXT, fp);
    // strcpy(buffer,root->option.enemy);
    //fgets(root->option.enemy, MAX_TXT, fp); //No tiene sentido
    // Use the function put enemy 

    // //We get the post_text
    // fgets(buffer, MAX_TXT, fp);
    // strcpy(buffer,root->option.post_txt);
    fgets(root->option.post_txt, MAX_TXT, fp);

    // //We get the question txt
    // fgets(buffer, MAX_TXT, fp);
    // strcpy(buffer,root->descions.question_txt);
    fgets(root->descions.question_txt, MAX_TXT, fp);
    // //We get the descriptions of  option 1 
    // fscanf(fp, "%d. ", buffer);
    // strcpy(buffer,root->descions.option[0].description);
    fgets(root->descions.option[0].description, MAX_TXT, fp);

    // //We get the descriptions of  option 2
    // fscanf(fp, "%d. ", buffer);
    // strcpy(buffer,root->descions.option[1].description);
    fgets(root->descions.option[1].description, MAX_TXT, fp);
    fclose(fp);
}


