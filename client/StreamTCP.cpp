/* класс для обмена через Connection приём/передача */

#include "StreamTCP.h"
#include <iostream>
#include <unistd.h>

namespace mychat {

	StreamTCP::~StreamTCP()
	{
		delete connection_;
	}

	void StreamTCP::setConnection(IConnection* connection)
	{
		connection_ = connection;
	}

	IConnection* StreamTCP::getConnection() const
	{
		return connection_;
	}

	int StreamTCP::sending(const char* str, std::size_t str_lenght)
	{
		if (!connection_) { std::cout << "No connection object\n"; return 1; };
		if (connection_->getClientSocket() == 0) connection_->connect();
		int status = 0;
		// отправка на сервер
		status += write(connection_->getClientSocket(), str, str_lenght);
		if (status == -1) {
			std::cout << "Writing to server failed!" << std::endl;
			connection_->disconnect();
			return 1;
		}
		return 0;
	}

	int StreamTCP::receiving() 
	{
		if (!connection_) { std::cout << "No connection object\n"; return 1; };
		if (connection_->getClientSocket() == 0) connection_->connect();
		// читаю сообщение
		int status = read(connection_->getClientSocket(), answer_.response, buffer_size_);
		if (status == -1) {
			std::cout << "Client read failed!" << std::endl;
			connection_->disconnect();
			return 1;
		}
		if (status == 0) {
			std::cout << "Client read EOF." << std::endl;
			connection_->disconnect();
			return 1;
		}
		if (status > 0) {
			answer_.response_lenght = status;
		}

		return 0;
	}

	size_t StreamTCP::getResponseLenght()
	{
		return answer_.response_lenght;
	}

	char* StreamTCP::getResponse()
	{
		return answer_.response;
	}
}

