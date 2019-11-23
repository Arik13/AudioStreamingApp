#pragma once

#define _CRT_SECURE_NO_DEPRECATE

#include "portaudio.h"
#include "PaWrapper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <boost/array.hpp>

#define SAMPLE_RATE (44100)
#define FRAMES_PER_BUFFER 32
#define NUM_CHANNELS (2)
#define DITHER_FLAG (0)
#define MONO (1)
#define STEREO (2)
#define PA_SAMPLE_TYPE paFloat32
#define SAMPLE_SILENCE (0.0f)

typedef float SAMPLE;

struct SampleData {
	int frameIndex;
	int maxFrameIndex;
	SAMPLE* recordedSamples;
};

class AudioStreamer {
public:
	virtual void stream(const SAMPLE* ptr, std::size_t size) = 0;
	virtual void stream(float left, float right) = 0;
};
PaStreamParameters getInputParameters(int channelCount, PaSampleFormat sampleType);
PaStreamParameters getOutputParameters(int channelCount, PaSampleFormat sampleType);