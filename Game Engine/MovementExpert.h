#pragma once
#include"BlackBoardAI.h"
class MovementExpert
{
public:
	BlackBoardAI* bbInstance = BlackBoardAI::Instance();
	MovementExpert();
	~MovementExpert();
	void CanPlayerSearch();
};

