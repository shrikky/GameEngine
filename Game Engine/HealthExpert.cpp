#include "HealthExpert.h"
#include <iostream>
#include "BlackBoardAI.h"
using namespace std;
HealthExpert::HealthExpert()
{
}


HealthExpert::~HealthExpert()
{
}

void HealthExpert::CheckHealth(){

	if (bbInstance->AIHEALTH < 50){
		bbInstance->_botstate = bbInstance->FLEE;
		bbInstance->canAttack = false;
	}
	if (bbInstance->_botstate == bbInstance->FLEE && !bbInstance->isSpotted)
		Heal();
	else
		bbInstance->_botstate = bbInstance->SEARCH;

}

void HealthExpert::Heal(){

	if (bbInstance->AIHEALTH < 100){
		std::cout << "With you hidden, the enemy is taking all the time in the world to heal itself" << endl;
			bbInstance->AIHEALTH += 10;
	}
}