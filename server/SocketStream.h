
/* Класс для отправки и приёма данных по сети 
	receiving			- получение данных,
	sending				- отправка данных,
	getResponse			- полученные данные,
	getResponseLenght	- размер полученных данных
*/

#pragma once
#include <unistd.h>
#include <memory>
#include "ConnectionTCPserver.h"

namespace mychat {
	class SocketStream
	{
		static const size_t buffer_size_{ 1024 };
		ConnectionTCPserver* connection_{ nullptr };

		struct ReceivingBuffer {
			char response[buffer_size_]{};
			int response_lenght{ 0 };
		} answer_;

	public:
		SocketStream();
		SocketStream(ConnectionTCPserver* connection);
		~SocketStream();

		int receiving();
		int sending(const char* str, size_t str_lenght);
		size_t getResponseLenght();
		char* getResponse();
	};
}

