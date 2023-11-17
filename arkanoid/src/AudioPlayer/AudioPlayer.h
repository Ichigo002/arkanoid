#ifndef AUDIO_PLAYER_H
#define AUDIO_PLAYER_H

#include <SDL_mixer.h>
#include <SDL.h>
#include <vector>
#include <string>
#include "../ErrorHandler/ErrorHandler.h"

class AudioPlayer
{
public:
	AudioPlayer();
	~AudioPlayer();

	// Volume in range 0 - 1
	void setVolume(float vol);
	// Volume in range 0 - 1
	float getVolume();

	/// <summary>
	/// Add sound effect. Clip must be shorter than 10 seconds
	/// </summary>
	/// <param name="filename">path to file .mp3 or .wav</param>
	/// <returns>-1 on fail or index number of sound</returns>
	int addSoundEffect(std::string filename);


	/// <summary>
	/// Add music clip. Clip must be longer than 10 seconds
	/// </summary>
	/// <param name="filename">path to file .mp3 or .wav</param>
	/// <returns>-1 on fail or index number of music clip</returns>
	int addMusic(std::string filename);


	/// <returns>0 on success or -1 on fail or -2 if previous music playing</returns>
	int playSound(int index);
	int playMusic(int index, bool looped = false);

	void pauseMusic();
	void resumeMusic();
	void stopPlayingMusic();

	bool isPlayingMusic();
	bool isPausedMusic();

	// I know it's bad practice but you know, it's the easiest way to do it :)
	float __control_sensitivity_option__ = 0.5f;
private:

	std::vector<Mix_Chunk*> vsound;
	std::vector<Mix_Music*> vmusic;

	float volume;
	bool pause;
};

#endif // !AUDIO_PLAYER_H
