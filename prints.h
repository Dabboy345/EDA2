#ifndef _PRINTS_H_
#define _PRINTS_H_

#include "common.h"
#include "combat.h"
#include "rpggame.h"

void print_game_name();
void print_menu();
void print_skills(Skill* skills);
void print_decision(Decision *choice, Character* plyr, Scenario* scene, Timestrike* stack);
void print_menu_option();

#endif


