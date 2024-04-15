/* Класс чат */

#include "Chat.h"
#include "../share/Message.h"
#include "../share/opcodes.h"
#include <iostream>
using namespace std;

namespace mychat {
	Chat::~Chat()
	{
		if (gateway_) delete gateway_;
		if (hasher_) delete hasher_;
		std::cout << "chat destructed\n";
	}

	int Chat::input(std::string& str, size_t str_lenght)
	{
		while (1) {
			getline(std::cin, str);
			if (str.size() > str_lenght || str_lenght == 0) {
				std::cout << "No more than " << str_lenght << " characters." << std::endl;
				return 1;
			}
			else return 0;
		}
	}

	void Chat::getChatHistory()
	{
		// история сообщений чата
		Message* mes{ nullptr };
		while (true) {
			gateway_->receiving();
			if (gateway_->getResponse()[0] == end_of_data_transmission) {
				break;
			}
			mes = new Message(gateway_->getResponse());
			mes->messageShow(); std::cout << std::endl;
			delete mes;
			gateway_->sending(&good, 1);
		}
	}

	void Chat::setStream(IStream* gateway)
	{
		gateway_ = gateway;
	}

	void Chat::setHasher(IHasher* hasher)
	{
		hasher_ = hasher;
	}

	int Chat::registerUser()
	{
		// ввод имя и пароль
		string user_name, user_pass;
		cout << "Input name: ";
		while (input(user_name, username_max_lenght)) {
			cout << "Input name: ";
		};
		cout << "Input pass: ";
		while (input(user_pass, username_max_lenght)) {
			cout << "Input pass: ";
		};

		// хэш пароля
		std::string hash(hasher_->getHash(user_pass.data(), user_pass.size()), hasher_->getLenghtHash());
		int32_t hashLenght = hash.size();

		// отправка запроса <код:char><user_name:string><messageSeparator:char><hashLenght:int32_t><hash:string>
		sending_buffer_.clear();
		sending_buffer_ = registration + user_name + messageSeparator + to_string(hashLenght) + hash;
		gateway_->sending(sending_buffer_.data(), sending_buffer_.size());

		// ответ сервера <код:char>
		gateway_->receiving();
		std::wcout << gateway_->getResponse()[0] << '\n';
		if (gateway_->getResponse()[0] == bad) {
			std::cout << "registration failed\n";
			return 1;
		}
		else if (gateway_->getResponse()[0] == user_exists) {
			std::cout << "there is already such a user\n";
			return 1;
		}
		std::cout << "registration success\n";
		return 0;
	}

	int Chat::loginUser()
	{
		// ввод имя и пароль
		string user_name, user_pass;
		cout << "Input name: ";
		while (input(user_name, username_max_lenght)) {
			cout << "Input name: ";
		};
		cout << "Input pass: ";
		while (input(user_pass, username_max_lenght)) {
			cout << "Input pass: ";
		};

		// хэш пароля
		std::string hash(hasher_->getHash(user_pass.data(), user_pass.size()), hasher_->getLenghtHash());
		int32_t hashLenght = hash.size();
		// отправка запроса <код:char><user_name:string><messageSeparator:char><hashLenght:int32_t><hash:string>
		sending_buffer_.clear();
		sending_buffer_ = login + user_name + messageSeparator + to_string(hashLenght) + hash;
		int status = gateway_->sending(sending_buffer_.data(), sending_buffer_.size());

		// ответ сервера <код:char>
		gateway_->receiving();
		if (gateway_->getResponse()[0] != good) {
			std::cout << "login failed\n";
			return 1;
		}
		std::cout << "login success\n\n";
		mainLoop(user_name);
		return 0;
	}

	int Chat::start_menu()
	{
		if (!hasher_) { std::cout << "No hash object\n"; return 0; }
		if (!gateway_) { std::cout << "No stream object\n"; return 0; }

		std::string str;
		while (true) {
			std::cout << "1 Login\n2 Register\n3 Exit\nPress 1, 2 or 3\n";
			std::getline(std::cin, str);
			if (str.size() > 1) continue;
			char val = str[0];
			if (val == '1' || val == '2' || val == '3') {

				switch (val) {
				case '1':
					if (loginUser() == 0) std::cout << "You are enter the chat\n";
					else std::cout << "You are not enter the chat\n";
					break;
				case '2':
					if (registerUser() == 0) std::cout << "Now login !\n";
					else std::cout << "Error registration\n";
					break;
				case '3':
					std::cout << "You are exit\n";
					exit(0);
				default:
					break;
				}
			}
		}
		return 0;
	}

	// цикл чата
	void Chat::mainLoop(string& name_from) {
		getChatHistory();
		cout << "Формат сообщения:\n\tЛичное: <кому><Enter><сообщение><Enter>\n\tВсем: <Enter><сообщение><Enter>" << endl;
		cout << "Напечатайте \"exit\" для выхода\n";
		string buf;
		while (1) {
			buf.clear();
			std::cout.clear();
			cout << "< " << name_from << " >:\t";
			std::cout << "<Кому>\t";
			getline(cin, buf);
			if (buf == "exit") break;

			// формируем строку для отправки <код><name_from><messageSeparator><name_to><messageSeparator><message><messageSeparator>
			sending_buffer_.clear();
			if (buf.empty()) 
				sending_buffer_ += shareMessage + name_from + messageSeparator + ' ' + messageSeparator;	// сообщение всем			
			else 
				sending_buffer_ += privatMessage + name_from + messageSeparator + buf + messageSeparator;	// личное сообщение
			buf.clear();
			std::cout << "<Сообщение>\t";
			getline(cin, buf);
			if (buf == "exit") break;
			sending_buffer_ += buf + messageSeparator;						// сообщение

			// отправка сообщения на сервер
			int status = gateway_->sending(sending_buffer_.data(), sending_buffer_.size());
		}
	}
}
