/*
	Класс сообщение
*/

#pragma once
#include <string>
#include <vector>

namespace mychat {
	class Message
	{
	private:
		struct MessageData {
			std::string message_date;
			std::string message_from;
			std::string message_to;
			std::string message;
		} message_;

		void messageRaw();
		std::string rawData_;

	public:
		Message() = default;
		Message (
			const std::string& message_date,
			const std::string& message_from,
			const std::string& message_to,
			const std::string& message
		);
		Message(char* messageData);
		~Message();

		std::string* getFrom();
		std::string* getTo();
		std::string* getMessage();
		std::string* getDate();

		void setFrom(std::string& str);
		void setTo(std::string& str);
		void setMessage(std::string& str);
		void setDate(std::string& str);

		void messageShow();
		std::string* getRawData();
	};
}
