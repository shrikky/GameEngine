#pragma once
#include "BlackBoardAI.h"
#include "InputHandler.h"
class Player
{
public:
	static Player* getInstance();
	int health = BlackBoardAI::Instance()->playerHealth;
	bool isKeyPressed;
	int attack = 5;
	void Update();
	void Attack();
	void DisplayStats();
	void Hide();
private:
	static Player* instance;
};

