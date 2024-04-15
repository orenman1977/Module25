/* 
	приём и передача
*/

#pragma once
#include "../share/IConnection.h"
#include "../share/IStream.h"

namespace mychat {
	class StreamTCP : public IStream
	{
	private:
		static const size_t buffer_size_{ 1024 };
		IConnection* connection_{ nullptr };

		struct ReceivingBuffer {
			char response[buffer_size_]{};				// ответ
			size_t response_lenght{ 0 };				// длина ответа
		} answer_;

	public:

		StreamTCP() = default;
		StreamTCP(IConnection* connection) : connection_(connection) {};
		~StreamTCP();

		void setConnection(IConnection* connection);
		IConnection* getConnection() const;
		int sending(const char* str, std::size_t str_lenght) override;
		int receiving() override;
		size_t getResponseLenght() override;
		char* getResponse() override;
	};
}
