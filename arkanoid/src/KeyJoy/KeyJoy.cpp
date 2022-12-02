#include "KeyJoy.h"

KeyJoy::KeyJoy(SDL_Event* eve)
	: eve(eve)
{
	checkConnectionJoystick();

	SetDeadZone(7500);

	kp_LR = 0;
}

KeyJoy::~KeyJoy()
{
}

float KeyJoy::getAction_MoveLR()
{
	if (jsconn)
	{
		float v = getMoveAxisHor();
		if (v != 0)
			return v;
	}

	if (getPressedKey(SDLK_a) || getPressedKey(SDLK_LEFT))
		kp_LR = -1;

	if (getPressedKey(SDLK_d) || getPressedKey(SDLK_RIGHT))
		kp_LR = 1;
	/// ------------ ///
	if (getReleasedKey(SDLK_a) || getReleasedKey(SDLK_LEFT) 
		|| getReleasedKey(SDLK_d) || getReleasedKey(SDLK_RIGHT))
		kp_LR = 0;

	return kp_LR;
}

float KeyJoy::getAction_MoveUD()
{
	if (jsconn)
	{
		float v = getMoveAxisVer();
		if (v != 0)
			return v;
	}

	if (getPressedKey(SDLK_w) || getPressedKey(SDLK_UP))
		kp_UD = -1;

	if (getPressedKey(SDLK_s) || getPressedKey(SDLK_DOWN))
		kp_UD = 1;
	/// ------------ ///
	if (getReleasedKey(SDLK_w) || getReleasedKey(SDLK_UP)
		|| getReleasedKey(SDLK_s) || getReleasedKey(SDLK_DOWN))
		kp_UD = 0;

	return kp_UD;
}

bool KeyJoy::getAction_Accept()
{
	return false;
}

bool KeyJoy::getAction_Cancel()
{
	return false;
}

bool KeyJoy::getAction_Next()
{
	return false;
}

bool KeyJoy::getAction_Prev()
{
	return false;
}

bool KeyJoy::getAction_Pause()
{
	return false;
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
bool KeyJoy::getPressedKey(SDL_KeyCode key)
{
	return eve->type == SDL_KEYDOWN && eve->key.keysym.sym == key;
}
bool KeyJoy::getReleasedKey(SDL_Keycode key)
{
	return eve->type == SDL_KEYUP && eve->key.keysym.sym == key;
}
void KeyJoy::events()
{
	checkConnectionJoystick();
}
