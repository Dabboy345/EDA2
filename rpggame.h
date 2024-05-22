#ifndef _RPGGAME_H_ //Here will put the functions regarding the funcionality of the game 
#define _RPGGAME_H_

#include "common.h"
#include "prints.h"

void try_skill(Skill *skll);

void get_skill(Skill *skill, int n);

Character* create_character(Skill *skills);

void put_enemy_info(char *line, Enemy *boss);

void get_info_decision(Decision *choice, int node_number, char *filename_txt);

Decision *create_desicion();

Scenario *create_inizialize_Scenario();

//Function to add a Decision to the Scenario
void addDecisionToScenario(Scenario *scenario, Decision *decision);

void *go_to_node_select_and_add(int node,char *filename,Scenario *scene);

void freeScenario(Scenario *scenario);

void saveLastDecisionData(Scenario* scenario, Decision* tempDecision);

int is_terminal(Decision *scene);

int get_valid_input();





#endif  