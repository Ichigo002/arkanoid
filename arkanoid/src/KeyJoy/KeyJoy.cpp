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
	if(jsconn && getPressedJoystickButton(JoystickButtons::Bottom))
		return true;
	return getPressedKey(SDLK_0, 13); // 13 -> Enter
}

bool KeyJoy::getAction_Cancel()
{
	if (jsconn && getPressedJoystickButton(JoystickButtons::Right))
		return true;
	return getPressedKey(SDLK_BACKSPACE);
}

bool KeyJoy::getAction_Next()
{
	if (js_action_next && getMoveAxisVer() == 0)
		js_action_next = false;

	if (jsconn && !js_action_next && getMoveAxisVer() > 0)
	{
		js_action_next = true;
		return true;
	}
	return getPressedKey(SDLK_DOWN) || getPressedKey(SDLK_s);
}

bool KeyJoy::getAction_Prev()
{
	if (js_action_prev && getMoveAxisVer() == 0)
		js_action_prev = false;

	if (jsconn && !js_action_prev && getMoveAxisVer() < 0)
	{
		js_action_prev = true;
		return true;
	}
	return getPressedKey(SDLK_UP) || getPressedKey(SDLK_w);
}

bool KeyJoy::getAction_Next_Hor()
{
	if (jsh_action_next && getMoveAxisHor() == 0)
		jsh_action_next = false;

	if (jsconn && !jsh_action_next && getMoveAxisHor() > 0)
	{
		jsh_action_next = true;
		return true;
	}
	return getPressedKey(SDLK_RIGHT) || getPressedKey(SDLK_d);
}

bool KeyJoy::getAction_Prev_Hor()
{
	if (jsh_action_prev && getMoveAxisHor() == 0)
		jsh_action_prev = false;

	if (jsconn && !jsh_action_prev && getMoveAxisHor() < 0)
	{
		jsh_action_prev = true;
		return true;
	}
	return getPressedKey(SDLK_LEFT) || getPressedKey(SDLK_a);
}

bool KeyJoy::getAction_Pause()
{
	if (jsconn && getPressedJoystickButton(JoystickButtons::Back))
		return true;
	return getPressedKey(SDLK_ESCAPE);
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
bool KeyJoy::getPressedKey(SDL_KeyCode key, int extra_no)
{
	return eve->type == SDL_KEYDOWN && ((extra_no == -1 && eve->key.keysym.sym == key) || eve->key.keysym.sym == extra_no);
}
bool KeyJoy::getReleasedKey(SDL_Keycode key, int extra_no)
{
	return eve->type == SDL_KEYUP && ((extra_no == -1 && eve->key.keysym.sym == key) || eve->key.keysym.sym == extra_no);
}
SDL_Event* KeyJoy::getEventData()
{
	return eve;
}
SDL_Joystick* KeyJoy::getJoystick()
{
	return joy;
}
void KeyJoy::events()
{
	checkConnectionJoystick();
}
