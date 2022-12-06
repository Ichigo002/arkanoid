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

	// Control: X Axis ; A,D ; LEFT,RIGHT 
	/// <returns>Move in direction: Left = -1, Right = 1</returns>
	float getAction_MoveLR();

	// Control: Y Axis ; W,S ; UP,DOWN
	/// <returns>Move in direction: Up = -1, Down = 1</returns>
	float getAction_MoveUD();

	// Control: A ; ENTER
	/// <returns>true if accept button clicked</returns>
	bool getAction_Accept();

	// Control: B ; BACKSPACE
	/// <returns>true if cancel button clicked</returns>
	bool getAction_Cancel();

	// Control: Only_Down Y Axis ; S ; DOWN
	/// WARNING! If two same this methods are within one call frame then second and evry next method won't work
	/// <returns>true if clicked button to go to next option in menu</returns>
	bool getAction_Next();

	// Control: Only_Up Y Axis ; W ; UP
	/// WARNING! If two same this methods are within one call frame then second and evry next method won't work
	/// <returns>true if clicked button to go to previous option in menu</returns>
	bool getAction_Prev();

	// Control: Only_Right X Axis ; D ; RIGHT
	/// WARNING! If two same this methods are within one call frame then second and evry next method won't work
	/// <returns>true if clicked button to go to next option in menu</returns>
	bool getAction_Next_Hor();

	// Control: Only_Left X Axis ; A ; LEFT
	/// WARNING! If two same this methods are within one call frame then second and evry next method won't work
	/// <returns>true if clicked button to go to previous option in menu</returns>
	bool getAction_Prev_Hor();

	// Control: BACK ; ESCAPE
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

	/// <param name="extra_no">If key is not booked in SDL_KeyCode then type keycode at int. Then keyCode is meaningless</param>
	bool getPressedKey(SDL_KeyCode key, int extra_no = -1);
	
	/// <param name="extra_no">If key is not booked in SDL_KeyCode then type keycode at int. Then keyCode is meaningless</param>
	bool getReleasedKey(SDL_Keycode key, int extra_no = -1);


	SDL_Event* getEventData();
	SDL_Joystick* getJoystick();
private:
	SDL_Joystick* joy;
	SDL_Event* eve;

	bool jsconn; // is joystick connected
	short int deadzone; // deadzone of axises 

	short int lastAxisHorV; // last axis horizontal value
	short int lastAxisVerV; // last axis vertical value

	int kp_LR; // move: left right
	int kp_UD; // move: up down

	bool js_action_next; // unclick next action
	bool js_action_prev; // unclick next action

	bool jsh_action_next; // unclick next action
	bool jsh_action_prev; // unclick next action
};

#endif