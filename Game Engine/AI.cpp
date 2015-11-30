#include "AI.h"
#include "BlackBoardAI.h"
#include <iostream>
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
	std::cout << "Enemy is attacking you" << std:: endl;
	int damage = rand() % 25 + 1;
	Player::getInstance()->health -= damage;
	std::cout << "AI Dealt: " << damage << " Damage to the player"<< std::endl;
	Player::getInstance()->DisplayStats();
	bbInstance->isAITurn = false;
}

void AI::Search(){
	if(!bbInstance->isSpotted)
	std::cout << "Searching for player  . . . . . " << std::endl;
	if (bbInstance->isSpotted){
		bbInstance->_botstate = bbInstance->ATTACK;
	}

}
void AI::DisplayStats(){
	if (*_AIhealth > 0)
	std::cout << "Enemy's Health: " << *_AIhealth << std::endl;
}