#include "UIButton.h"

const int CLIP_MOUSEOVER = 0;
const int CLIP_MOUSEOUT = 1;
const int CLIP_MOUSEDOWN = 2;
const int CLIP_MOUSEUP = 3;


SDL_Surface *buttonSheet = NULL;

SDL_Event event;


UIButton* UIButton::s_pInstance = 0;

UIButton::UIButton()
{

}

void UIButton::setClips() {
	clips[CLIP_MOUSEOVER].x = 0;
	clips[CLIP_MOUSEOVER].y = 0;
	clips[CLIP_MOUSEOVER].w = 320;
	clips[CLIP_MOUSEOVER].h = 240;

	clips[CLIP_MOUSEOUT].x = 320;
	clips[CLIP_MOUSEOUT].y = 0;
	clips[CLIP_MOUSEOUT].w = 320;
	clips[CLIP_MOUSEOUT].h = 240;

	clips[CLIP_MOUSEDOWN].x = 0;
	clips[CLIP_MOUSEDOWN].y = 240;
	clips[CLIP_MOUSEDOWN].w = 320;
	clips[CLIP_MOUSEDOWN].h = 240;

	clips[CLIP_MOUSEUP].x = 320;
	clips[CLIP_MOUSEUP].y = 240;
	clips[CLIP_MOUSEUP].w = 320;
	clips[CLIP_MOUSEUP].h = 240;
}

SDL_Surface *load_image(std::string filename)
{
	//The image that's loaded
	SDL_Surface* loadedImage = NULL;

	//The optimized surface that will be used
	SDL_Surface* optimizedImage = NULL;

	//Load the image
	loadedImage = IMG_Load(filename.c_str());
	SDL_SetColorKey(loadedImage, SDL_TRUE, SDL_MapRGB(loadedImage->format, 0, 0xFF, 0xFF));
	//If the image loaded
	if (loadedImage != NULL)
	{
		//Create an optimized surface
		optimizedImage = SDL_ConvertSurfaceFormat(loadedImage, SDL_PIXELFORMAT_RGB444, 0);

		//Free the old surface
		//SDL_FreeSurface(loadedImage);

		//If the surface was optimized
		if (optimizedImage != NULL)
		{
			//Color key surface
			SDL_SetColorKey(optimizedImage, SDL_TRUE, SDL_MapRGB(optimizedImage->format, 0, 0xFF, 0xFF));
		}
	}

	//Return the optimized surface
	return loadedImage;
}

void loadFiles() {
	buttonSheet = load_image("button.png");
}

void UIButton::init(int x, int y, int w, int h) {
	loadFiles();
	box.x = x;
	box.y = y;
	box.w = w;
	box.h = h;
	setClips();
	clip = &clips[CLIP_MOUSEOUT];
}


UIButton::~UIButton()
{
}

void UIButton::handleEvents()
{
	//The mouse offsets
	int x = 0, y = 0;

	//If the mouse moved
	if (event.type == SDL_MOUSEMOTION)
	{
		//Get the mouse offsets
		x = event.motion.x;
		y = event.motion.y;

		//If the mouse is over the button
		if ((x > box.x) && (x < box.x + box.w) && (y > box.y) && (y < box.y + box.h))
		{
			//Set the button sprite
			clip = &clips[CLIP_MOUSEOVER];
		}
		//If not
		else
		{
			//Set the button sprite
			clip = &clips[CLIP_MOUSEOUT];
		}
	}
	//If a mouse button was pressed
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		//If the left mouse button was pressed
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			//Get the mouse offsets
			x = event.button.x;
			y = event.button.y;

			//If the mouse is over the button
			if ((x > box.x) && (x < box.x + box.w) && (y > box.y) && (y < box.y + box.h))
			{
				//Set the button sprite
				clip = &clips[CLIP_MOUSEDOWN];
			}
		}
	}
	//If a mouse button was released
	if (event.type == SDL_MOUSEBUTTONUP)
	{
		//If the left mouse button was released
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			//Get the mouse offsets
			x = event.button.x;
			y = event.button.y;

			//If the mouse is over the button
			if ((x > box.x) && (x < box.x + box.w) && (y > box.y) && (y < box.y + box.h))
			{
				//Set the button sprite
				clip = &clips[CLIP_MOUSEUP];
			}
		}
	}
}

void applySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL)
{
	//Holds offsets
	SDL_Rect offset;

	//Get offsets
	offset.x = x;
	offset.y = y;

	//Blit
	SDL_BlitSurface(source, clip, destination, &offset);
}

void UIButton::show()
{
	//Show the button
	applySurface(box.x, box.y, buttonSheet, screen, clip);
}

