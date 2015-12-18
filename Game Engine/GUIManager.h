#pragma once
#include <string>
using namespace std;
class GUIManager
{
public:
	static GUIManager* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new GUIManager();
			return s_pInstance;
		}

		return s_pInstance;
	}

	void renderUI();
	void displayText(char* mess, int value);
	void displayText2(char* mess, int value);
private:
	static GUIManager* s_pInstance;
	
};

