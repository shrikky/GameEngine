#include "AI.h"
#include "BlackBoardAI.h"
#include <iostream>
#include "GUIManager.h"
#include "Player.h"
AI::AI()
{
	_AIhealth = &BlackBoardAI::Instance()->AIHEALTH;
}


AI::~AI()
{
	
}
void AI::Update(){
	if (bbInstance->_botstate == bbInstance->SEARCH)
	Search();
	if (bbInstance->_botstate == bbInstance->ATTACK && bbInstance->isSpotted && bbInstance->isAITurn)
	Attack();

	DisplayStats();
}
void AI::Attack(){
	GUIManager::Instance()->displayText("Enemy is attacking you", 0);
	//std::cout << "Enemy is attacking you" << std:: endl;
	int damage = rand() % 25 + 1;
	Player::getInstance()->health -= damage;
	GUIManager::Instance()->displayText("AI Dealt:u", damage);
	//std::cout << "AI Dealt: " << damage << " Damage to the player"<< std::endl;
	Player::getInstance()->DisplayStats();
	bbInstance->isAITurn = false;
}

void AI::Search(){
	if(!bbInstance->isSpotted)
		GUIManager::Instance()->displayText("Searching foir plkayer", 0);
	if (bbInstance->isSpotted){
		bbInstance->_botstate = bbInstance->ATTACK;
	}

}
void AI::DisplayStats(){
	if (*_AIhealth > 0)
		GUIManager::Instance()->displayText("Enemy health", *_AIhealth);
}