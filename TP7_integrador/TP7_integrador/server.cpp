#include "server.h"
#include "paquete.h"
#include <string>
#include <iostream>

const int HELLO_PORT = 15667;

std::string server::wait_for_message() {
	
	std::string res;
	boost::system::error_code error;
	char buf[sizeof(package_data)];
	do {
		this->socket_forServer->read_some(boost::asio::buffer(buf, 30), error);
	} while ((error.value() == WSAEWOULDBLOCK));
	res = buf;
	return res;
}

void server::start_to_listen() {
	server_acceptor->accept(*socket_forServer);

	std::cout << "Waiting for somebody to connect.. :( " << std::endl;
	socket_forServer->non_blocking(true);
	this->server_acceptor->accept(*(this->socket_forServer));
}

void server::sendMessage(char *buf, int size) {

	size_t len;
	boost::system::error_code error;

	this->socket_forServer->non_blocking(true);

	do {
		len = socket_forServer->write_some(boost::asio::buffer(buf, size), error);
	} while ((error.value() == WSAEWOULDBLOCK));

	if (error)
		std::cout << "Error while trying to connect to server " << error.message() << std::endl;
}

std::string server::receiveMessage() {

	boost::system::error_code error;
	char buf[PKGSIZE]; //El buffer debe ser del tamaño del paquete.

	size_t len = socket_forServer->read_some(boost::asio::buffer(buf), error);

	if (error) {
		std::cout << "Error while trying to connect to server " << error.message() << std::endl;
		failure = 1;
		return ERR_STR;
	}

	std::string auxString = "";

	for (int i = 0; i < strlen(buf); i++) {
		 auxString[i] = buf[i];
	}
	auxString[strlen(buf)] = '\0';

	return auxString;
}

server::server() {
	IO_handler = new boost::asio::io_service();
	socket_forServer = new boost::asio::ip::tcp::socket(*IO_handler);
	server_acceptor = new boost::asio::ip::tcp::acceptor(*IO_handler,
	boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), HELLO_PORT));
	std::cout << std::endl << "Ready. Port " << HELLO_PORT << " created" << std::endl;
}

server::~server() {
	std::cout << "closing server \n";
	server_acceptor->close();
	socket_forServer->close();
	delete server_acceptor;
	delete socket_forServer;
	delete IO_handler;
}