#ifdef GAMEAUDIO_EXPORTS
#define GAMEAUDIO_API __declspec(dllexport)
#else
#define GAMEAUDIO_API __declspec(dllimport)
#endif

#ifndef GAMEAUDIO_H
#define GAMEAUDIO_H

#include "AudioErr.h"

class GAMEAUDIO_API CGameAudio
{
public:
	CGameAudio( void );
	virtual AudioError SetSoundPan( int iID, int iPan );
	virtual AudioError SetMusicVolume( int iLevel );
	virtual AudioError SetSoundVolume( int iID, int iLevel );
	virtual AudioError RefreshMusic();
	virtual AudioError StopMusic();
	virtual AudioError PlayMusic( char* cname );
	virtual AudioError StopSound( int iID );
	virtual AudioError PlayGameSound( int iID );
	virtual AudioError LoadSound( int iID, char* cname, int soundtype );
	virtual AudioError CreateSoundBuffer();
	virtual AudioError ShutAudio();
	virtual AudioError InitAudio( HWND hwnd );

};

class GAMEAUDIO_API CDXAudio;

#endif