/* класс для установки соединения TCP клиента */
// только соединение/разъединение

#include "ConnectionTCPclient.h"
#include <iostream>

namespace mychat {
	ConnectionTCPclient::ConnectionTCPclient(std::string& ip, size_t port)
	{
		ip_ = ip;
		port_ = port;
	}

	ConnectionTCPclient::~ConnectionTCPclient()
	{
		if (client_socket_) { close(client_socket_); }
	}

	int ConnectionTCPclient::connect()
	{
		client_socket_ = socket(AF_INET, SOCK_STREAM, 0);
		if (client_socket_ == -1) {
			std::cout << "Creation of Socket failed!" << std::endl;
			return 1;
		}
		connect_options_.sin_addr.s_addr = inet_addr(ip_.data());
		connect_options_.sin_port = htons(port_);
		connect_options_.sin_family = AF_INET;

		int status_ = ::connect(client_socket_, (sockaddr*)&connect_options_, sizesockaddr_);
		if (status_ == -1) {
			std::cout << "Connection with the server failed.!" << std::endl;
			disconnect();
			return 1;
		}
		std::cout << "Connection with the server established..." << std::endl;
		return 0;
	}

	int ConnectionTCPclient::disconnect()
	{
		if (client_socket_) {
			close(client_socket_);
			client_socket_ = 0;
		}
		std::cout << "Disconnection..." << std::endl;
		return 0;
	}

	int ConnectionTCPclient::getClientSocket()
	{
		return client_socket_;
	}
}

