#include "server.h"


const int HELLO_PORT = 12345;


string server::wait_for_message() {
	string res;
	boost::system::error_code error;
	char buf[1 + 255 + 1];
	do {
		this->socket_forServer->read_some(boost::asio::buffer(buf, 30), error);
	} while ((error.value() == WSAEWOULDBLOCK));
	res = buf;
	return res;
}
void server::start_to_listen() {
	server_acceptor->accept(*socket_forServer);
}

void server::sendMessage(char *buf, int size) {

	size_t len;
	boost::system::error_code error;

	do {
		len = socket_forServer->write_some(boost::asio::buffer(buf, size), error);
	} while ((error.value() == WSAEWOULDBLOCK));

	if (error)
		std::cout << "Error while trying to connect to server " << error.message() << std::endl;
}

server::server() {
	IO_handler = new boost::asio::io_service();
	socket_forServer = new boost::asio::ip::tcp::socket(*IO_handler);
	server_acceptor = new boost::asio::ip::tcp::acceptor(*IO_handler,
		boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), HELLO_PORT));
	cout << std::endl << "Ready. Port " << HELLO_PORT << " created" << std::endl;
}

server::~server() {
	cout << "closing server \n";
	server_acceptor->close();
	socket_forServer->close();
	delete server_acceptor;
	delete socket_forServer;
	delete IO_handler;
}