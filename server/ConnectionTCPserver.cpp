
/* Класс для установки соединений TCP сервера */

#include "ConnectionTCPserver.h"
#include <iostream>

namespace mychat {
	ConnectionTCPserver::ConnectionTCPserver(int port)
	{
		port_ = port;
	}

	ConnectionTCPserver::~ConnectionTCPserver() {
		close(clients_);
		close(server_socket_);
		std::cout << "~ConnectionTCPserver()\n";
	}

	int ConnectionTCPserver::getClientSockets()
	{
		return clients_;
	}

	int ConnectionTCPserver::startListen()
	{
		int status = 0;
		server_socket_ = socket(AF_INET, SOCK_STREAM, 0);
		if (server_socket_ == -1) {
			std::cout << "Creation of Socket failed!" << std::endl;
			return 1;
		}

		connect_options_.sin_addr.s_addr = htonl(ip_);
		connect_options_.sin_port = htons(port_);
		connect_options_.sin_family = AF_INET;

		status = bind(server_socket_, (sockaddr*)&connect_options_, sizesockaddr_);
		if (status == -1) {
			std::cout << "Socket binding failed.!" << std::endl;
			exit(1);
		}

		status = listen(server_socket_, querysize_);
		if (status == -1) {
			std::cout << "Socket is unable to listen for new connections.!" << std::endl;
			return 1;
		}
		else {
			std::cout << "Server is listening for new connection... " << std::endl;
		}
		return 0;
	}

	int ConnectionTCPserver::accepting() {
		int status = 0;
		status = accept(server_socket_, (sockaddr*)&connect_options_, &sizesockaddr_);
		if (status == -1) {
			std::cout << "Server is unable to accept the data from client.!" << std::endl;
			return 1;
		}
		clients_ = status;
		std::cout << "Connection with client established..." << std::endl;
		return 0;

	}

	void ConnectionTCPserver::disconnectClient(int client_socket)
	{
		close(client_socket);
		clients_ = 0;
		std::cout << "Client disconnected..." << std::endl;
	}
}
