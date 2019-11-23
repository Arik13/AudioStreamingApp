#include "portaudio.h"
#include <iostream>

void check(PaError err) {
	if (err != paNoError) {
		std::cout << Pa_GetErrorText(err) << std::endl;
		throw PaErrorCode(err);
	}
}
void PaOpenStream(PaStream** stream,
	const PaStreamParameters* inputParameters,
	const PaStreamParameters* outputParameters,
	double sampleRate,
	unsigned long framesPerBuffer,
	PaStreamFlags streamFlags,
	PaStreamCallback* streamCallback,
	void* userData)
{
	check(Pa_OpenStream(stream, inputParameters, outputParameters, sampleRate, framesPerBuffer, streamFlags, streamCallback, userData));
}

void PaStartStream(PaStream* stream) {
	check(Pa_StartStream(stream));
}

void PaCloseStream(PaStream* stream) {
	check(Pa_CloseStream(stream));
}

void PaInitialize() {
	check(Pa_Initialize());
}