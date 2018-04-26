#pragma once
#define _WIN32_WINNT 0x0501
#include <string>

#include "boost/asio.hpp"
#include "boost/function.hpp"
#include "boost/bind.hpp"



class server {
public:
	server();
	void start_to_listen();
	void sendMessage(char *buf, int size);
	std::string wait_for_message();
	~server();

private:
	boost::asio::io_service*  IO_handler;
	boost::asio::ip::tcp::socket* socket_forServer;
	boost::asio::ip::tcp::acceptor* server_acceptor;
};



