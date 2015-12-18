#include "Player.h"
#include <iostream>
#include "GUIManager.h"
Player* Player::instance = 0;

Player* Player::getInstance(){
	if (instance == 0){
		instance = new Player;
	}
	return instance;

}
void Player::Update(){

	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_A))
	Attack();

	//Hide();
	//DisplayStats(); 
}

void Player::Attack(){
	/*char input;
	cout << "----------------------------------------------------------------------------------------- \n" << std::endl;
	cout << "Press A for attack and H for hide" << endl;
	cin >> input;

	if (input == 'a' || input == 'A')
	{
		int damage = rand() % 30 + 1;
		BlackBoardAI::Instance()->AIHEALTH -= damage;
		std::cout << "Player Dealt " << damage << " Damage to the Enemy" << std::endl;
		BlackBoardAI::Instance()->isSpotted = true;
	}
	if (input == 'h' || input == 'H'){
		BlackBoardAI::Instance()->isSpotted = false;
		health += 5;
	}*/

		int damage = rand() % 30 + 1;
		BlackBoardAI::Instance()->AIHEALTH -= damage;
	//	std::cout << "Player Dealt " << damage << " Damage to the Enemy" << std::endl;
		GUIManager::Instance()->displayText2("Damage dealt by the player to the enemy:", damage);
		BlackBoardAI::Instance()->isSpotted = true; 
		BlackBoardAI::Instance()->isAITurn = true;
		//printf("A is pressed\n");
	

}
void Player::Hide(){
	BlackBoardAI::Instance()->isSpotted = false;
	BlackBoardAI::Instance()->isAITurn = true;
	health += 5;

}
void Player::DisplayStats(){
	if (health > 0)
			GUIManager::Instance()->displayText2("player Health:", health);
}

