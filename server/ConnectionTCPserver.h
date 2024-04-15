
/* Класс для установки соединения TCP сервера
- создать объект класса
- startListen		запуск очереди прослушки сокета
- accepting			приём соединений клиентов
- disconnectClient	закрытие соединений клиентов
- getClientSockets	геттер соединений
*/

#pragma once

#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <list>

namespace mychat {
	class ConnectionTCPserver
	{
	private:
		int server_socket_{ 0 };
		int clients_;
		sockaddr_in connect_options_{ 0 };
		socklen_t sizesockaddr_{ sizeof(connect_options_) };
		in_addr_t ip_{ INADDR_ANY };
		int port_{ 7777 };
		int querysize_{ 10 };

	public:
		ConnectionTCPserver() = default;
		ConnectionTCPserver(int port);
		~ConnectionTCPserver();

		int startListen();
		int accepting();
		void disconnectClient(int client_socket);
		int getClientSockets();
	};
}

