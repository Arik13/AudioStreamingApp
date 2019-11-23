#pragma once

#define _CRT_SECURE_NO_DEPRECATE

#include "PaFunctions.h"
#include <fstream>

PaStreamParameters getInputParameters(int channelCount, PaSampleFormat sampleType) {
	PaStreamParameters inputParameters;
	inputParameters.device = Pa_GetDefaultInputDevice();
	if (inputParameters.device == paNoDevice) {
		fprintf(stderr, "Error: No default input device.\n");
		exit(1);
	}
	inputParameters.channelCount = channelCount;
	inputParameters.sampleFormat = sampleType;
	inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency;
	inputParameters.hostApiSpecificStreamInfo = NULL;
	return inputParameters;
}


PaStreamParameters getOutputParameters(int channelCount, PaSampleFormat sampleType) {
	PaStreamParameters outputParameters;
	outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
	if (outputParameters.device == paNoDevice) throw "Error: No default output device.\n";

	outputParameters.channelCount = channelCount;
	outputParameters.sampleFormat = sampleType;
	outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
	outputParameters.hostApiSpecificStreamInfo = NULL;
	return outputParameters;
}