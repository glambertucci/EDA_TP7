
#define _WIN32_WINNT 0x0501

#include "client.h"
#include "paquete.h"
#include <string>
#include <boost/asio.hpp>
#include <boost/chrono.hpp>
#include <boost/timer/timer.hpp>
#include <boost/exception_ptr.hpp> 
#include "general.h"
const string CLIENT_PORT = "15667";

client::client() {
	IO_handler = new boost::asio::io_service();
	socket_forClient = new boost::asio::ip::tcp::socket(*IO_handler);
	client_resolver = new boost::asio::ip::tcp::resolver(*IO_handler);
	failure = 0;
}

client::~client() {
	socket_forClient->close();
	delete client_resolver;
	delete socket_forClient;
	delete IO_handler;
}

void client::startConnection(const char* host) {
	endpoint = client_resolver->resolve(
		boost::asio::ip::tcp::resolver::query(host, CLIENT_PORT));
	cout << "Trying to connect to " << host << " on port " << CLIENT_PORT << endl;
	try {
		boost::asio::connect(*socket_forClient, endpoint);
	}
	catch (exception const&  ex) {
		cout << "could not connect" << '\n';
		failure = 1;
	}
}

bool client::success() {
	return !failure;
}

std::string client::receiveMessage() {
	static int notfirst=-2;//Nice
	Timer time;
	boost::system::error_code error;
	char buf[PKGSIZE]; //El buffer debe ser del tama�o del paquete.
	if (notfirst==0) {
		time.start();
	}
	do {
		this->socket_forClient->read_some(boost::asio::buffer(buf, 30), error);
		if (notfirst == 0) {
			time.stop();
			if (time.getTime() > TIMEOUT)
				break;
		}
	} while ((error.value() == WSAEWOULDBLOCK));

	if(notfirst == 0){
		if (time.getTime() < TIMEOUT)
		{
			if (error) {
				std::cout << "Error while trying to connect to server " << error.message() << std::endl;
				failure = 1;
				return ERR_STR;
			}
			std::string auxString = "";
			for (int i = 0; (i < strlen(buf)); i++) {
				auxString += buf[i];
			}
			return auxString;
		}
		return NOPACKAGE;
	}
	if (notfirst < 0)
		notfirst++;
		if (error) {
			std::cout << "Error while trying to connect to server " << error.message() << std::endl;
			failure = 1;
			return ERR_STR;
		}
		std::string auxString = "";
		for (int i = 0; (i < strlen(buf)); i++)
			auxString += buf[i];

		return auxString;
}

void client::nonblock(void)
{
	this->socket_forClient->non_blocking(true);
}
void client::send_message(const char *msg, int size) {
	size_t len;
	boost::system::error_code error;
	len = socket_forClient->write_some(boost::asio::buffer(msg, size), error);
}