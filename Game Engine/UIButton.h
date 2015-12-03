#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <iostream>
#pragma once
class UIButton
{
public:
	static UIButton* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new UIButton();
			return s_pInstance;
		}

		return s_pInstance;
	}

	void init(int x, int y, int w, int h);
	void handleEvents();
	void show();
	void setClips();
	SDL_Rect clips[4];
	SDL_Surface *screen;
	UIButton();
	~UIButton();

private:
	UIButton(const UIButton&);
	UIButton &operator=(const UIButton&);

	static UIButton* s_pInstance;

	SDL_Rect box;
	SDL_Rect* clip;
};

