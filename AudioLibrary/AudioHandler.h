#pragma once
#include <boost/lockfree/queue.hpp>

class AudioHandler {
public:
	AudioHandler(boost::lockfree::spsc_queue<float>* queue);
	~AudioHandler();
	void run();
private:
	boost::lockfree::spsc_queue<float>* audioQueue;
};