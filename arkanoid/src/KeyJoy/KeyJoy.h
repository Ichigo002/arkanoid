#ifndef KEYJOY_H
#define KEYJOY_H

#include <SDL.h>
#include <iostream>
#include <cmath>
#include <limits>
#include "../ErrorHandler/ErrorHandler.h"

enum JoystickButtons
{
	Bottom = 0,// 'A'
	Right = 1, // 'B'
	Left = 2,  // 'X'
	Top = 3,   // 'Y'

	LB = 4,    // Left Button
	RB = 5,    // Right Button

	Back = 6,  // Back [left aside xbox guide]
	Start = 7, // Start[right aside xbox guide]

	LSB = 8,   // Left Stick Button
	RSB = 9,   // Right Stick Button
};

class KeyJoy
{
public:
	KeyJoy(SDL_Event* eve);
	~KeyJoy();

/* --- READY CONTROLS */

	/// <returns>Move in direction: Left = -1, Right = 1</returns>
	float getAction_MoveLR();

	/// <returns>Move in direction: Up = -1, Down = 1</returns>
	float getAction_MoveUD();

	/// <returns>true if accept button clicked</returns>
	bool getAction_Accept();

	/// <returns>true if cancel button clicked</returns>
	bool getAction_Cancel();

	/// <returns>true if clicked button to go to next option in menu</returns>
	bool getAction_Next();

	/// <returns>true if clicked button to go to previous option in menu</returns>
	bool getAction_Prev();

	/// <returns>true if pause button clicked to stop game</returns>
	bool getAction_Pause();

	//bool getAction_()

	/// <summary>
	/// Shall be called before other keyjoy methods every new frame
	/// </summary>
	void events();

/* --- JOYSTICK METHODS */

	/// <summary>
	/// Return translated move from axis
	/// </summary>
	/// <returns>value of move between -1 and 1</returns>
	float getMoveAxisHor();
	float getMoveAxisVer();

	/// <summary>
	/// Returns true if button clicked
	/// </summary>
	/// <param name="btn">what button from JoystickButtons</param>
	bool getPressedJoystickButton(JoystickButtons btn);

	/// <summary>
	/// Check if joystick is disconnected or connected back
	/// </summary>
	void checkConnectionJoystick();

	/// <summary>
	/// Deadzone must be POSITIVE value.
	/// </summary>
	void SetDeadZone(short int deadzone);

/* --- KEYBOARD METHODS */

	bool getPressedKey(SDL_KeyCode key);

	bool getReleasedKey(SDL_Keycode key);

private:
	SDL_Joystick* joy;
	SDL_Event* eve;

	bool jsconn; // is joystick connected
	short int deadzone; // deadzone of axises 

	short int lastAxisHorV; // last axis horizontal value
	short int lastAxisVerV; // last axis vertical value

	int kp_LR; // move speed left right
	int kp_UD; // move speed up down
};

#endif