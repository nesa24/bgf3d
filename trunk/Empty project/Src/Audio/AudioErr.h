#ifndef AUDIOERR_H
#define AUDIOERR_H

enum AudioError
{
	AUDIO_OK,		//right

	ERR_CREATE,		//����ʱ����
	ERR_EMPTY,		//�޶���
	ERR_AD_VIRTUAL,	//�����麯��
	ERROR_NO
};

#define SOUND_KBPS_8 0
#define SOUND_KBPS_16 1

#endif