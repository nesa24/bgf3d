#ifndef AUDIOERR_H
#define AUDIOERR_H

enum AudioError
{
	AUDIO_OK,		//right

	ERR_CREATE,		//创建时出错
	ERR_EMPTY,		//无对象
	ERR_AD_VIRTUAL,	//调用虚函数
	ERROR_NO
};

#define SOUND_KBPS_8 0
#define SOUND_KBPS_16 1

#endif