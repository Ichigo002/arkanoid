#include "AudioPlayer.h"

AudioPlayer::AudioPlayer()
{
	Mix_Init(MIX_INIT_MP3);

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048))
	{
		throwError(__FUNCTION__, "Init mix open audio");
	}
}

AudioPlayer::~AudioPlayer()
{
	Mix_Quit();
	for (Mix_Music* m : vmusic)
	{
		Mix_FreeMusic(m);
		m = nullptr;
	}
	for (Mix_Chunk* c : vsound)
	{
		Mix_FreeChunk(c);
		c = nullptr;
	}
}

void AudioPlayer::setVolume(float vol)
{
	if (vol >= 0 && vol <= 1)
		volume = vol;
}

float AudioPlayer::getVolume()
{
	return volume;
}

int AudioPlayer::addSoundEffect(std::string filename)
{
	Mix_Chunk* tmpch = Mix_LoadWAV(filename.c_str());
	if (tmpch == NULL)
	{
		//throwError(__FUNCTION__, "Couldn't load audio chunk from file: " + filename);
		return -1;
	}
	vsound.push_back(tmpch);
	return vsound.size() - 1;
}

int AudioPlayer::addMusic(std::string filename)
{
	Mix_Music* tmpmus = Mix_LoadMUS(filename.c_str());
	if (tmpmus == NULL)
	{
		//throwError(__FUNCTION__, "Couldn't load music object from file: " + filename);
		return -1;
	}
	vmusic.push_back(tmpmus);
	return vmusic.size() - 1;
}

int AudioPlayer::playSound(int index)
{
	if (index < 0 || index >= vsound.size())
		return -1;
	return Mix_PlayChannel(-1, vsound[index], 0);
}

int AudioPlayer::playMusic(int index, bool looped)
{
	if (index < 0 || index >= vmusic.size())
		return -1;
	if (Mix_PlayingMusic() == 1)
		return -2;
	pause = false;
	return Mix_PlayMusic(vmusic[index], 0);
}

void AudioPlayer::pauseMusic()
{
	Mix_PauseMusic();
	pause = true;
}

void AudioPlayer::resumeMusic()
{
	Mix_ResumeMusic();
	pause = false;
}

void AudioPlayer::stopPlayingMusic()
{
	Mix_HaltMusic();
	pause = false;
}

bool AudioPlayer::isPlayingMusic()
{
	return Mix_PlayingMusic();
}

bool AudioPlayer::isPausedMusic()
{
	return pause;
}
