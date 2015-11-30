#include "MovementExpert.h"
#include <iostream>

MovementExpert::MovementExpert()
{
}


MovementExpert::~MovementExpert()
{
}

void MovementExpert::CanPlayerSearch(){

	if (!bbInstance->isSpotted){
		bbInstance->_botstate = bbInstance->SEARCH;
	}
	else
	{
		bbInstance->_botstate = bbInstance->ATTACK;
	}
}