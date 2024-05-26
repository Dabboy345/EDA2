#ifndef _RPGGAME_H_ //Here will put the functions regarding the funcionality of the game 
#define _RPGGAME_H_

#include "common.h"
#include "prints.h"

void try_skill(Skill *skll);

void get_skill(Skill *skill, int n);

void choose_skill(Skill *skills, Character *player);

Character* create_character(Skill *skills);

void put_enemy_info(char *line, Enemy *boss);

void get_info_decision(Decision *choice, int node_number, char *filename_txt);

Decision *create_desicion();

Scenario *create_inizialize_Scenario();

//Function to add a Decision to the Scenario
void addDecisionToScenario(Scenario *scenario, Decision *decision);

void go_to_node_select_and_add(int node,char *filename,Scenario *scene, Character* plyr);

void freeScenario(Scenario *scenario);

void saveLastDecisionData(Scenario* scenario, Decision* tempDecision);

int is_terminal(Decision *scene);

int get_valid_input(int first, int size);

int get_last_node_numeber(Scenario *scenario);

void save_game(Scenario *scene, Character *character, char* buffer);

int run_game(int node_number, char *filename, Character *plyr);

int load_game_and_play(char* buffer, Character* plyr, int* last_node_number);

//order skills
void swap(Skill* p1, Skill* p2);
int partition(Skill arr[], int low, int high);
void quickSort(Skill arr[], int low, int high);
void order_skills_dmg();



#endif  