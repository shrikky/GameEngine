#include "InputHandler.h"

InputHandler* InputHandler::s_pInstance = 0;

InputHandler::InputHandler() : m_keystates(0),
m_bJoysticksInitialised(false),
m_mousePosition(new glm::ivec2(0))
{
	// create button states for the mouse
	for (int i = 0; i < 3; i++)
	{
		m_mouseButtonStates.push_back(false);
	}
}

InputHandler::~InputHandler()
{
	// delete anything we created dynamically
	delete m_keystates;
	delete m_mousePosition;

	// clear our arrays
	m_joystickValues.clear();
	m_joysticks.clear();
	m_buttonStates.clear();
	m_mouseButtonStates.clear();
}

void InputHandler::clean()
{
	// we need to clean up after ourselves and close the joysticks we opened
	if (m_bJoysticksInitialised)
	{
		for (int i = 0; i < SDL_NumJoysticks(); i++)
		{
			SDL_JoystickClose(m_joysticks[i]);
		}
	}
}

void InputHandler::initialiseJoysticks()
{
	// if we haven't already initialised the joystick subystem, we will do it here
	if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
	{
		SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	}

	// get the number of joysticks, skip init if there aren't any
	if (SDL_NumJoysticks() > 0)
	{
		for (int i = 0; i < SDL_NumJoysticks(); i++)
		{
			// create a new joystick
			SDL_Joystick* joy = SDL_JoystickOpen(i);

			// if the joystick opened correctly we need to populate our arrays
			if (SDL_JoystickOpen(i))
			{
				// push back into the array to be closed later
				m_joysticks.push_back(joy);

				// create a pair of values for the axes, a vector for each stick
				m_joystickValues.push_back(std::make_pair(new glm::ivec2(0), new glm::ivec2(0)));

				// create an array to hold the button values
				std::vector<bool> tempButtons;

				// fill the array with a false value for each button
				for (int j = 0; j < SDL_JoystickNumButtons(joy); j++)
				{
					tempButtons.push_back(false);
				}
				// push the button array into the button state array
				m_buttonStates.push_back(tempButtons);
			}
			else
			{
				// if there was an error initialising a joystick we want to know about it
				std::cout << SDL_GetError();
			}
		}

		// enable joystick events
		SDL_JoystickEventState(SDL_ENABLE);
		m_bJoysticksInitialised = true;

		std::cout << "Initialised " << m_joysticks.size() << " joystick(s)";
	}
	else
	{
		m_bJoysticksInitialised = false;
	}
}

void InputHandler::reset()
{
	m_mouseButtonStates[0] = false;
	m_mouseButtonStates[1] = false;
	m_mouseButtonStates[2] = false;
}

bool InputHandler::isKeyDown(SDL_Scancode key) const
{
	if (m_keystates != 0)
	{
		if (m_keystates[key] == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	return false;
}

int InputHandler::getAxisX(int joy, int stick) const
{
	if (m_joystickValues.size() > 0)
	{
		if (stick == 1)
		{
			return m_joystickValues[joy].first->x;
		}
		else if (stick == 2)
		{
			return m_joystickValues[joy].second->x;
		}
	}
	return 0;
}

int InputHandler::getAxisY(int joy, int stick) const
{
	if (m_joystickValues.size() > 0)
	{
		if (stick == 1)
		{
			return m_joystickValues[joy].first->y;
		}
		else if (stick == 2)
		{
			return m_joystickValues[joy].second->y;
		}
	}
	return 0;
}

bool InputHandler::getButtonState(int joy, int buttonNumber) const
{
	return m_buttonStates[joy][buttonNumber];
}

bool InputHandler::getMouseButtonState(int buttonNumber) const
{
	return m_mouseButtonStates[buttonNumber];
}

glm::ivec2* InputHandler::getMousePosition() const
{
	return m_mousePosition;
}

bool InputHandler::update()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			return false;
			break;

		case SDL_JOYAXISMOTION:
			onJoystickAxisMove(event);
			break;

		case SDL_JOYBUTTONDOWN:
			onJoystickButtonDown(event);
			break;

		case SDL_JOYBUTTONUP:
			onJoystickButtonUp(event);
			break;

		case SDL_MOUSEMOTION:
			onMouseMove(event);
			break;

		case SDL_MOUSEBUTTONDOWN:
			onMouseButtonDown(event);
			break;

		case SDL_MOUSEBUTTONUP:
			onMouseButtonUp(event);
			break;

		case SDL_KEYDOWN:
			onKeyDown();
			break;

		case SDL_KEYUP:
			onKeyUp();
			break;

		default:
			break;
		}
	}

	return true;
}

void InputHandler::onKeyDown()
{
	m_keystates = SDL_GetKeyboardState(0);
}

void InputHandler::onKeyUp()
{
	m_keystates = SDL_GetKeyboardState(0);
}

void InputHandler::onMouseMove(SDL_Event &event)
{
	m_mousePosition->x = (event.motion.x);
	m_mousePosition->y = (event.motion.y);
}

void InputHandler::onMouseButtonDown(SDL_Event &event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		m_mouseButtonStates[0] = true;
	}

	if (event.button.button == SDL_BUTTON_MIDDLE)
	{
		m_mouseButtonStates[1] = true;
	}

	if (event.button.button == SDL_BUTTON_RIGHT)
	{
		m_mouseButtonStates[2] = true;
	}
}

void InputHandler::onMouseButtonUp(SDL_Event &event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		m_mouseButtonStates[0] = false;
	}

	if (event.button.button == SDL_BUTTON_MIDDLE)
	{
		m_mouseButtonStates[1] = false;
	}

	if (event.button.button == SDL_BUTTON_RIGHT)
	{
		m_mouseButtonStates[2] = false;
	}
}

void InputHandler::onJoystickAxisMove(SDL_Event &event)
{
	int whichOne = event.jaxis.which;

	// left stick move left or right
	if (event.jaxis.axis == 0)
	{
		if (event.jaxis.value > m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->x = (1);
		}
		else if (event.jaxis.value < -m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->x = (-1);
		}
		else
		{
			m_joystickValues[whichOne].first->x = (0);
		}
	}

	// left stick move up or down
	if (event.jaxis.axis == 1)
	{
		if (event.jaxis.value > m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->y = (1);
		}
		else if (event.jaxis.value < -m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->y = (-1);
		}
		else
		{
			m_joystickValues[whichOne].first->y = (0);
		}
	}

	// right stick move left or right
	if (event.jaxis.axis == 3)
	{
		if (event.jaxis.value > m_joystickDeadZone)
		{
			m_joystickValues[whichOne].second->x = (1);
		}
		else if (event.jaxis.value < -m_joystickDeadZone)
		{
			m_joystickValues[whichOne].second->x = (-1);
		}
		else
		{
			m_joystickValues[whichOne].second->x = (0);
		}
	}

	// right stick move up or down
	if (event.jaxis.axis == 4)
	{
		if (event.jaxis.value > m_joystickDeadZone)
		{
			m_joystickValues[whichOne].second->y = (1);
		}
		else if (event.jaxis.value < -m_joystickDeadZone)
		{
			m_joystickValues[whichOne].second->y = (-1);
		}
		else
		{
			m_joystickValues[whichOne].second->y = (0);
		}
	}
}

void InputHandler::onJoystickButtonDown(SDL_Event &event)
{
	int whichOne = event.jaxis.which;

	m_buttonStates[whichOne][event.jbutton.button] = true;
}

void InputHandler::onJoystickButtonUp(SDL_Event &event)
{
	int whichOne = event.jaxis.which;

	m_buttonStates[whichOne][event.jbutton.button] = false;
}