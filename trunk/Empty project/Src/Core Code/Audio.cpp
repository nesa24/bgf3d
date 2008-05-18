#include "StdAfx.h"
#include "Audio.h"

Audio::Audio()
{
	m_bSoundOn = true;
	m_pAudio = NULL;
	m_vctMusicRes.clear();
	m_vctSoundRes.clear();
}

Audio::~Audio()
{
}

bool Audio::CreateAudio()
{
	m_pAudio = CreateGameAudio( hwndMain );
	return true;
}

bool Audio::InitAudio()
{
	/************************************************************************/
	/* 加载所有音效资源                                                                     */
	/************************************************************************/
	int size = (int)m_vctSoundRes.size();
	for ( int i = 0; i < size; ++i )
	{
		m_pAudio->CreateSoundBuffer();
		m_pAudio->LoadSound( i, (char*)(m_vctSoundRes[i].c_str()), m_vctSoundImpulse[i] );
	}

	return true;
}

void Audio::PlayGameSound( const int iID )
{
	if ( m_bSoundOn )
		m_pAudio->PlayGameSound( iID );
}

void Audio::PlayMusic( const int iID )
{
	if ( m_bSoundOn )
		m_pAudio->PlayMusic( ((char*)m_vctMusicRes[iID].c_str()) );
}

void Audio::RefreshMusic()
{
	if ( m_pAudio )
	{
		if ( false == m_bSoundOn )
			StopMusic();

		m_pAudio->RefreshMusic();
	}
}

void Audio::SetMusicVolume( int iLevel )
{
	m_pAudio->SetMusicVolume( iLevel );
}

void Audio::SetSoundPan( int iID, int iPan )
{
	m_pAudio->SetSoundPan( iID, iPan );
}

void Audio::SetSoundVolume( int iID, int iLevel )
{
	m_pAudio->SetSoundVolume( iID, iLevel );
}

void Audio::ShutAudio()
{
	m_pAudio->ShutAudio();
}

void Audio::StopMusic()
{
	m_pAudio->StopMusic();
}

void Audio::StopSound( int iID )
{
	m_pAudio->StopSound( iID );
}

void Audio::SoundOn()
{
	m_bSoundOn = true;
}

void Audio::SoundOff()
{
	m_bSoundOn = false;
}