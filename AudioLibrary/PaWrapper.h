#include "portaudio.h"

void PaOpenStream(PaStream** stream,
	const PaStreamParameters* inputParameters,
	const PaStreamParameters* outputParameters,
	double sampleRate,
	unsigned long framesPerBuffer,
	PaStreamFlags streamFlags,
	PaStreamCallback* streamCallback,
	void* userData);
void PaStartStream(PaStream* stream);
void PaCloseStream(PaStream* stream);
void PaInitialize();