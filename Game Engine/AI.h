#pragma once

#include "BlackBoardAI.h"
class AI
{
public:
	BlackBoardAI* bbInstance = BlackBoardAI::Instance();
	int *_AIhealth;
	AI();
	~AI();
	void Update();
	void Search();
	void Attack();
	void DisplayStats();
};

