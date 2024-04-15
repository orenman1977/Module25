/*
	Интерфейс соединения
*/
#pragma once
namespace mychat {
	class IConnection {
	public:
		virtual ~IConnection() = default;
		virtual int connect() = 0;
		virtual int disconnect() = 0;
		virtual int getClientSocket() = 0;
	};
}
