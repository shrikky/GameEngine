#pragma once
#include "AI.h"
class StrategicExpert
{
public:
	BlackBoardAI* bbInstance = BlackBoardAI::Instance();
	StrategicExpert();
	~StrategicExpert();
	AI* _aiBot = new AI();
	void ExecuteStrategy();
};

