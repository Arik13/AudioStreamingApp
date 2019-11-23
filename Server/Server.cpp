// async_udp_echo_server.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2019 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <boost/lockfree/spsc_queue.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include "AudioHandler.h"

using boost::asio::ip::udp;
namespace ba = boost::asio;

const short PORT = 13251;

class server {
public:
	server(ba::io_context& io_context, short port) : socket_(io_context, udp::endpoint(udp::v4(), port)), audioQueue(4096), audioHandler(&audioQueue) {
		std::cout << "Server instantiated" << std::endl;
		socket_.async_receive_from(
			ba::buffer(data_, max_length),
			sender_endpoint_,
			boost::bind(
				&server::handle_receive_from, this,
				ba::placeholders::error,
				ba::placeholders::bytes_transferred));
		audioHandler.run();
	}

	void handle_receive_from(const boost::system::error_code& error, size_t bytes_recvd) {
		if (!error && bytes_recvd > 0) {
			for (int i = 0; i < bytes_recvd/4; i++) {
				audioQueue.push(data_[i]);
			}
		}
		socket_.async_receive_from(
			ba::buffer(data_, max_length),
			sender_endpoint_,
			boost::bind(
				&server::handle_receive_from, this,
				ba::placeholders::error,
				ba::placeholders::bytes_transferred));
	}
private:
	udp::socket socket_;
	udp::endpoint sender_endpoint_;
	enum { max_length = 1024 };
	float data_[max_length];
	boost::lockfree::spsc_queue<float> audioQueue;
	AudioHandler audioHandler;
};

int main() {
	try {
		ba::io_context io_context;

		server s(io_context, PORT);

		std::cout << "Run\n";
		io_context.run();
	}
	catch (std::exception &e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}
	std::cout << "End\n";
	return 0;
}