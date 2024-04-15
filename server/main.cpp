// Точка входа - инициализация объектов
//TODO чтение настроек из файла
//TODO личные сообщения
#include "Server.h"
#include <sstream>
#include <memory>
#include <iostream>
using namespace std;

int main()
{

    int port = 7777;
    std::unique_ptr<mychat::Server> server = std::make_unique<mychat::Server>(new mychat::WorkDB, new mychat::SocketStream(new mychat::ConnectionTCPserver(port)));
    server->start();
	return 0;
}
