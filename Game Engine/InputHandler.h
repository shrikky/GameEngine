#pragma once
#include "SDL/SDL.h"

#include <GLM/glm.hpp>

#include <iostream>
#include <vector>
#include <utility>

class InputHandler
{
public:

	static InputHandler* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new InputHandler();
		}

		return s_pInstance;
	}

	// init joysticks
	void initialiseJoysticks();
	bool joysticksInitialised() { return m_bJoysticksInitialised; }

	void reset();

	// update and clean the input handler
	bool update();
	void clean();

	// joystick events
	int getAxisX(int joy, int stick) const;
	int getAxisY(int joy, int stick) const;
	bool getButtonState(int joy, int buttonNumber) const;

	// keyboard events
	bool isKeyDown(SDL_Scancode key) const;

	// mouse events
	bool getMouseButtonState(int buttonNumber) const;
	glm::ivec2* getMousePosition() const;

private:

	InputHandler();
	~InputHandler();

	InputHandler(const InputHandler&);
	InputHandler& operator=(const InputHandler&);

	// private functions to handle different event types

	// handle keyboard events
	void onKeyDown();
	void onKeyUp();

	// handle mouse events
	void onMouseMove(SDL_Event& event);
	void onMouseButtonDown(SDL_Event& event);
	void onMouseButtonUp(SDL_Event& event);

	// handle joysticks events
	void onJoystickAxisMove(SDL_Event& event);
	void onJoystickButtonDown(SDL_Event& event);
	void onJoystickButtonUp(SDL_Event& event);

	// member variables

	// keyboard specific
	const Uint8* m_keystates;

	// joystick specific
	std::vector<std::pair<glm::ivec2*, glm::ivec2*>> m_joystickValues;
	std::vector<SDL_Joystick*> m_joysticks;
	std::vector<std::vector<bool>> m_buttonStates;
	bool m_bJoysticksInitialised;
	static const int m_joystickDeadZone = 10000;

	// mouse specific
	std::vector<bool> m_mouseButtonStates;
	glm::ivec2* m_mousePosition;

	// singleton
	static InputHandler* s_pInstance;
};


