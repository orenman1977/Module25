// Точка входа для приложения клиента чата.
#include "Chat.h"
#include "StreamTCP.h"
#include "ConnectionTCPclient.h"
#include "../share/sha1.h"
#include <iostream>
#include <memory>
#include <string>
#include <locale>

int main()
{
	setlocale(LC_ALL, "RU-ru.UTF-8");
	//TODO чтение настроек из файла
	std::string serverIP = "127.0.0.1";
	size_t port = 7777;

	mychat::ConnectionTCPclient* connection = new mychat::ConnectionTCPclient(serverIP, port);
	connection->connect();
	mychat::StreamTCP* stream = new mychat::StreamTCP(connection);
	mychat::CypherSHA1* hasher = new mychat::CypherSHA1;
	std::unique_ptr<mychat::Chat> chat = std::make_unique<mychat::Chat>();	
	chat->setHasher(hasher);
	chat->setStream(stream);
	chat->start_menu();
 	std::cout << "\nClient closing..." << std::endl;
	return 0;
}
