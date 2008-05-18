#ifndef AUDIOFUNS_H

#include "GameAudio.h"
#include "AudioErr.h"

/**	@brief 创建音频对象，对其进行初始化
* 	@param hwnd 当前窗口句柄
* 	@return
* 		return 创建好的音频对象指针
*/
CGameAudio GAMEAUDIO_API *CreateGameAudio( HWND hwnd );

#endif
