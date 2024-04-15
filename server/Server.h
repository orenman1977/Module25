/* 
	Класс сервер 
*/
#pragma once
#include "WorkDB.h"
#include "SocketStream.h"
#include "../share/User.h"
#include "../share/Message.h"

namespace mychat {
	class Server
	{
		WorkDB* db_;					// база данных
		SocketStream* gateway_;			// канал обмена

	public:
		Server();
		Server(WorkDB* db, SocketStream* ss);
		~Server();

		int start();
	};
}

