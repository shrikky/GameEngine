#include "Arbiter.h"
#include <iostream>
#include "BlackBoardAI.h"
using namespace std;
Arbiter::Arbiter()
{
}


Arbiter::~Arbiter()
{
}
void Arbiter::Update(){
	if (BlackBoardAI::Instance()->AIHEALTH <= 50)
		BlackBoardAI::Instance()->_botstate = BlackBoardAI::Instance()->FLEE;

	switch (BlackBoardAI::Instance()->_botstate)
	{
	case 0: 
		moveExpert->CanPlayerSearch();
		break;
	case 1:
		stratExpert->ExecuteStrategy();
		break;
	case 2:
		healExpert->CheckHealth();
		break;

	default:
		break;
	}
}
