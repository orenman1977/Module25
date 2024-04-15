/* класс для установки соединения TCP клиента для Линукс */
// только соединение/разъединение
#pragma once

#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include "../share/IConnection.h"

namespace mychat {
	class ConnectionTCPclient : public IConnection {
	private:
		int client_socket_{ 0 };
		sockaddr_in connect_options_{ 0 };
		socklen_t sizesockaddr_{ sizeof(connect_options_) };
		std::string ip_{ "127.0.0.1" };
		int port_{ 7777 };

	public:

		ConnectionTCPclient() = default;
		ConnectionTCPclient(std::string& ip, size_t port);
		~ConnectionTCPclient();

		int connect() override;
		int disconnect() override;
		int getClientSocket() override;
	};
}
