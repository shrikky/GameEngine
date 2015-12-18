#include "StrategicExpert.h"
#include <iostream>
#include <stdlib.h>
#include "GUIManager.h"

StrategicExpert::StrategicExpert()
{
}


StrategicExpert::~StrategicExpert()
{
}
// Solving the problem
void StrategicExpert::ExecuteStrategy(){
	if (bbInstance->AIHEALTH > 50){
		bbInstance->canAttack = true;
	}
	else
	{
		//std::cout << "Enemy is Retrating, kill the enemy now by attacking. If you go into hiding, the enemy might heal and come back stronger than you" << std::endl;
		//GUIManager::Instance()->message = "Enemy is Retrating, kill the enemy now by attacking. If you go into hiding, the enemy might heal and come back stronger than you";
		GUIManager::Instance()->displayText("Enemy is Retrating, kill the enemy now by attacking. If you go into hiding, the enemy might heal and come back stronger than you",0);
		
		bbInstance->_botstate = bbInstance->FLEE;
		bbInstance->canAttack = false;
	}
	
}

