#pragma once

#define _WIN32_WINNT 0x0501

#include <iostream>
#include <cstdio>
#include <boost/asio.hpp>
#include <boost/chrono.hpp>
#include <boost/timer/timer.hpp>
#include <boost/exception_ptr.hpp> 


#include "timer.h"

#define NOPACKAGE "N"

using namespace std;

class client {
public:
	client();
	void startConnection(const char* host);
	std::string receiveMessage();
	void send_message(const char *msg, int size);
	~client();
	bool success();
	void nonblock();

private:
	boost::asio::io_service* IO_handler;
	boost::asio::ip::tcp::socket* socket_forClient;
	boost::asio::ip::tcp::resolver* client_resolver;
	boost::asio::ip::tcp::resolver::iterator endpoint;

	bool failure;

};

