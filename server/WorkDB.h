
/* Класс для работы с базой данных MySQL (БД могут быть разные)
*	- подключение/отключение БД
	- формирование запросов к БД
	- отправка/приём запросов к БД
*/

#pragma once
#include <mysql.h>
#include <string>
#include "User.h"
#include "Message.h"

namespace mychat {
	class WorkDB
	{
	private:
		MYSQL* mysql_{ nullptr };
		MYSQL_RES* mysql_res_{ nullptr };
		MYSQL_ROW row_{ nullptr };
		std::vector<std::string> table_content_;

		int dbConnect();
		void dbDisconnect();

	public:
		WorkDB() = default;
		~WorkDB();
		int userLogin(User* user);			// успех/не успех
		int userRegister(User* user);		// успех/не успех
		std::vector<std::string>* messageHistory(User* user);
		int storeMessage(Message* mes);
	};
}

