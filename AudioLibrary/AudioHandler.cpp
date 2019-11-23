#include <portaudio.h>
#include "boost/lockfree/spsc_queue.hpp"
#include "PaFunctions.h"
#include "AudioHandler.h"


int callback(
	const void* inputBuffer,
	void* outputBuffer,
	unsigned long framesPerBuffer,
	const PaStreamCallbackTimeInfo* timeInfo,
	PaStreamCallbackFlags statusFlags,
	void* userData)
{
	boost::lockfree::spsc_queue<SAMPLE>* audioStream = (boost::lockfree::spsc_queue<SAMPLE>*) userData;
	SAMPLE* wptr = (SAMPLE*)outputBuffer;
	for (int i = 0; i < framesPerBuffer; i++) {
		if (!audioStream->pop(*wptr))* wptr = SAMPLE_SILENCE; // *(wptr - 1);
		wptr++;
		if (NUM_CHANNELS == 2) {
			if (!audioStream->pop(*wptr))* wptr = SAMPLE_SILENCE; // *(wptr - 1);
			wptr++;
		}
	}
	return paContinue;
}

AudioHandler::AudioHandler(boost::lockfree::spsc_queue<float>* queue) { 
	audioQueue = queue;
}
AudioHandler::~AudioHandler() {
	delete audioQueue;
}
void AudioHandler::run() {
	PaInitialize();
	PaStream* stream;
	PaOpenStream(&stream, NULL, &getOutputParameters(STEREO, PA_SAMPLE_TYPE), SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, callback, audioQueue);
	PaStartStream(stream);
}