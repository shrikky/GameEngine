
#include <iostream>
#include "BlackBoardAI.h"
using namespace std;
BlackBoardAI* BlackBoardAI::instance = 0;
BlackBoardAI* BlackBoardAI::Instance(){

	if (instance == 0){
		instance = new BlackBoardAI;

	}
	return instance;

}
