#pragma once
#ifndef _INCL_BB
#define _INCL_BB

using namespace std;
class BlackBoardAI
{
public:
	static BlackBoardAI* Instance();

	bool canAttack = false;
	bool isSpotted = false;
	bool hasReached = false;
	bool hasDestroyed = false;
	bool isAITurn = false;
	int AIHEALTH = 100;
	int movementSpeed = 0;
	int playerHealth = 100;
	enum BotState
	{
		SEARCH, ATTACK, FLEE
	};
	BotState _botstate = SEARCH;

private:
	static BlackBoardAI* instance;
		
};


#endif

