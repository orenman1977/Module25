/* Класс чата */
// UI, hash, ввод\вывод сообщений в поток

#pragma once
#include "../share/IHasher.h"
#include "../share/IStream.h"
#include <string>
#include <vector>

namespace mychat {
	class Chat
	{
	private:
		static const size_t username_max_lenght = 10;
		static const size_t user_password_max_lenght = 10;
		std::string sending_buffer_;
		IStream* gateway_{ nullptr };
		IHasher* hasher_{ nullptr };

		int input(std::string& str, size_t str_lenght);
		void getChatHistory();

	public:
		~Chat();

		void setStream(IStream* gateway);
		void setHasher(IHasher* hasher);

		int registerUser();
		int loginUser();
		int start_menu();
		void mainLoop(std::string& name);
	};
}
