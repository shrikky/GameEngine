#pragma once
#include "BlackBoardAI.h"
class HealthExpert
{
public:
	BlackBoardAI* bbInstance = BlackBoardAI::Instance();
	HealthExpert();
	~HealthExpert();
	void CheckHealth();
	void Heal();
};

