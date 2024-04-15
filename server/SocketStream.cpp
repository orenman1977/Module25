/* Класс для обмена через Connection приём/передача */

#include "SocketStream.h"
#include <iostream>
namespace mychat {
	SocketStream::SocketStream()
	{
		connection_ = new ConnectionTCPserver();
		connection_->startListen();
		std::cout << "SocketStream()...\n";

	}

	SocketStream::SocketStream(ConnectionTCPserver* connection)
	{
		connection_ = connection;
		if(connection_) connection_->startListen();
	}

	SocketStream::~SocketStream()
	{
		delete connection_;
		std::cout << "~SocketStream()...\n";
	}


	int SocketStream::receiving()
	{
		if (connection_->getClientSockets() == 0) connection_->accepting();
		int status = read(connection_->getClientSockets(), answer_.response, buffer_size_);
		if (status == -1) {
			std::cout << "Server read failed!" << std::endl;
			connection_->disconnectClient(connection_->getClientSockets());
			return 1;
		}
		if (status == 0) {
			std::cout << "Server read EOF!" << std::endl;
			connection_->disconnectClient(connection_->getClientSockets());
			return 1;
		}
		if (status > 0) {
			answer_.response_lenght = status;
		}
		if (answer_.response == "quit") exit(0);
		return 0;
	}

	int SocketStream::sending(const char* str, size_t str_lenght)
	{
		if (connection_->getClientSockets() == 0) connection_->accepting();
		int status = 0;
		// отправка
		while (status < str_lenght) {
			status += write(connection_->getClientSockets(), str, str_lenght);
			if (status == -1) {
				std::cout << "Writing to client failed!" << std::endl;
				connection_->disconnectClient(connection_->getClientSockets());
				return 1;
			}
		}
		return 0;
	}

	size_t SocketStream::getResponseLenght()
	{
		return answer_.response_lenght;
	}

	char* SocketStream::getResponse()
	{
		return answer_.response;
	}
}

