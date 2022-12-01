#include "KeyJoy.h"

KeyJoy::KeyJoy(SDL_Event* eve)
	: eve(eve)
{
	checkConnectionJoystick();

	SetDeadZone(7500);
}

KeyJoy::~KeyJoy()
{
}

float KeyJoy::getMoveAxisHor()
{
	if (!jsconn)
		return 0.0f;

	// axis 0 -> Horizontal
	if (eve->type == SDL_JOYAXISMOTION && (unsigned int)eve->jaxis.axis == 0)
	{
		lastAxisHorV = eve->jaxis.value;
	}

	if (abs(lastAxisHorV) > deadzone)
	{
		if (lastAxisHorV > 0)
			return (float)(lastAxisHorV - deadzone) / (float)(SHRT_MAX - deadzone);
		else
			return (float)(-lastAxisHorV - deadzone) / (float)(SHRT_MIN + deadzone);
	}
	else
		return 0.0f;
}

float KeyJoy::getMoveAxisVer()
{
	if (!jsconn)
		return 0.0f;

	// axis 1 -> Vertical
	if (eve->type == SDL_JOYAXISMOTION && (unsigned int)eve->jaxis.axis == 1)
	{
		lastAxisHorV = eve->jaxis.value;
	}

	if (abs(lastAxisHorV) > deadzone)
	{
		if (lastAxisHorV > 0)
			return (float)(lastAxisHorV - deadzone) / (float)(SHRT_MAX - deadzone);
		else
			return (float)(-lastAxisHorV - deadzone) / (float)(SHRT_MIN + deadzone);
	}
	else
		return 0.0f;
}

bool KeyJoy::getPressedJoystickButton(JoystickButtons btn)
{
	if (jsconn && eve->type == SDL_JOYBUTTONDOWN)
		return (int)eve->jbutton.button == btn;
	return false;
}

void KeyJoy::checkConnectionJoystick()
{
	if (SDL_NumJoysticks() > 0)
	{
		if (jsconn)
			return;
		joy = SDL_JoystickOpen(0);
		jsconn = true;
	}
	else
	{
		jsconn = false;
	}
}

void KeyJoy::SetDeadZone(short int deadzone)
{
	this->deadzone = deadzone;
}
void KeyJoy::events()
{
	checkConnectionJoystick();
}
