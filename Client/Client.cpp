#pragma once

#include "PaFunctions.h"
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <iostream>

#define IPADDRESS "127.0.0.1"
#define UDP_PORT 13251

using boost::asio::ip::udp;
using boost::asio::ip::address;
using namespace boost::asio;

class Streamer : public AudioStreamer {
public:
	Streamer() : socket(io_service) {
		remote_endpoint = udp::endpoint(address::from_string(IPADDRESS), UDP_PORT);
		socket.open(udp::v4());
	}
	void stream(const SAMPLE* samplePtr, std::size_t size) {
		socket.send_to(buffer(samplePtr, size), remote_endpoint, 0, err);
	}
	void stream(float left, float right) {
		socket.send_to(buffer({ left, right }), remote_endpoint, 0, err);
	}
private:
	io_service io_service;
	udp::socket socket;
	udp::endpoint remote_endpoint;
	boost::system::error_code err;
};

static int callback(const void* inputBuffer,
	void* outputBuffer,
	unsigned long framesPerBuffer,
	const PaStreamCallbackTimeInfo* timeInfo,
	PaStreamCallbackFlags statusFlags,
	void* userData)
{
	AudioStreamer* audioStreamer = (AudioStreamer*)userData;
	const SAMPLE* rptr = (const SAMPLE*)inputBuffer;
	for (long i = 0; i < framesPerBuffer; i++) {
		audioStreamer->stream(*rptr, *(rptr + 1));
		rptr += 2;
	}
	return paContinue;
}

int main() {
	SampleData data;
	try {
		PaInitialize();
		Streamer streamer;
		PaStream* stream;
		PaOpenStream(&stream, &getInputParameters(STEREO, PA_SAMPLE_TYPE), NULL, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, callback, &streamer);
		PaStartStream(stream);

		PaError err;
		while ((err = Pa_IsStreamActive(stream)) == 1) {
			Pa_Sleep(1000);
		}
	}
	catch (PaErrorCode errorCode) {
		std::cout << Pa_GetErrorText(errorCode) << std::endl;
	}
}