#ifndef __IAUDIOCONTEXT_H
#define __IAUDIOCONTEXT_H

#include "AudioObject.h"

class IAudioContext
{
public:
	//IAudioContext();
	virtual ~IAudioContext() {}
	virtual void playAudio(AudioObject& ao) = 0;
	virtual void pauseAudio(AudioObject& ao) = 0;
	virtual void stopAudio(AudioObject& ao) = 0;

private:

};

#endif