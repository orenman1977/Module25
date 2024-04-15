#include "WorkDB.h"
#include "../share/opcodes.h"
#include <iostream>
#include <string>
#include <sstream>

namespace mychat {
	WorkDB::~WorkDB()
	{
		if (mysql_) {
			mysql_close(mysql_);
		}
		std::cout << "~WorkDB()...\n";
	}

	int WorkDB::dbConnect()
	{
		mysql_ = mysql_init(mysql_);
		if (mysql_ == nullptr) {
			std::cout << "error init " << mysql_error(mysql_) << std::endl;
			return 1;
		}

		if (!mysql_real_connect(mysql_, "localhost", "root", "0909", "chat", 3306, NULL, 0)) {
			std::cout << "error connect  " << mysql_error(mysql_) << std::endl;
			return 1;
		}

		std::cout << "Connecting DB established...\n";
		return 0;
	}

	void WorkDB::dbDisconnect()
	{
		mysql_close(mysql_);
		mysql_ = nullptr;
		std::cout << "Connection DB closed...\n" << std::endl;
	}

	// SELECT login, password FROM chat.users WHERE login = "name" AND password = "pass"
	int WorkDB::userLogin(User* user)
	{
		std::string query("SELECT login, password FROM chat.users WHERE login = \"");
		query.append(*user->getName());
		query.append("\" AND password = \"");
		query.append(*user->getPassword());
		query.append("\"");
		std::cout << "query " << query << "\nquery size " << query.size() << std::endl;
		dbConnect();
		int status = mysql_query(mysql_, query.data());
		if (!status) {
			mysql_res_ = mysql_store_result(mysql_);
			if (mysql_res_) {
				if (mysql_num_rows(mysql_res_)) {
					std::cout << "user found\n";
					mysql_free_result(mysql_res_);
					dbDisconnect();
					return 0;	// пользователь найден успех
				}
			}
			else {
				std::cout << "Error SQL store:  " << mysql_error(mysql_) << std::endl;
				return 1;
			}
		}
		else {
			std::cout << "Error SQL query:  " << mysql_error(mysql_) << std::endl;
			return 1;
		}
		std::cout << "user not found\n";
		mysql_free_result(mysql_res_);
		dbDisconnect();
		return 1;				// пользователь не найден неудача
	}

	// INSERT INTO chat.users ( login, password) values ("user1","pass1");
	int WorkDB::userRegister(User* user)
	{
		int status = userLogin(user);
		if (!status) return 2;			// такой пользователь уже есть неудача

		std::string query("INSERT INTO chat.users ( login, password) values (\"");
		query.append(*user->getName());
		query.append("\", \"");
		query.append(*user->getPassword());
		query.append("\")");

		dbConnect();
		status = mysql_query(mysql_, query.data());
		if (status) {
			std::cout << "Error SQL query:  " << mysql_error(mysql_) << std::endl;
			return 1;
		}
		dbDisconnect();
		return 0;						// регистрация успешна
	}

	std::vector<std::string>* WorkDB::messageHistory(User* user)
	{
		table_content_.clear();
		std::ostringstream os;
		std::string query("SELECT * FROM (SELECT * FROM chat.user_messages ORDER BY id DESC LIMIT 10) t ORDER BY id");
		dbConnect();
		int status = mysql_query(mysql_, query.data());
		if (!status) {
			mysql_res_ = mysql_store_result(mysql_);
			if (mysql_res_) {
				while (row_ = mysql_fetch_row(mysql_res_)) {
					for (size_t i = 1; i < mysql_num_fields(mysql_res_); ++i) {
						//std::cout << row_[i];
						os << row_[i] << messageSeparator;
					}
					table_content_.push_back(os.str());
					os.str("");
				}
				mysql_free_result(mysql_res_);
				dbDisconnect();
				return &table_content_;
			}
			else {
				std::cout << "Error SQL store:  " << mysql_error(mysql_) << std::endl;
				return nullptr;
			}
		}
		else {
			std::cout << "Error SQL query:  " << mysql_error(mysql_) << std::endl;
			return nullptr;
		}
		mysql_free_result(mysql_res_);
		dbDisconnect();
		return nullptr;
	}

	// INSERT INTO chat.user_messages (message_date, message_from, message_to, message) VALUES (Now(), from, to, message)
	int WorkDB::storeMessage(Message* mes)
	{
		std::string query("INSERT INTO chat.user_messages ( message_date, message_from, message_to, message) values (");
		query.append("Now()");
		query.append(", \"");

		query.append(*mes->getFrom());
		query.append("\", \"");
		query.append(*mes->getTo());
		query.append("\", \"");
		query.append(*mes->getMessage());
		query.append("\")");

		dbConnect();
		int status = mysql_query(mysql_, query.data());
		if (status) {
			std::cout << "Error SQL query:  " << mysql_error(mysql_) << std::endl;
			return 1;
		}
		dbDisconnect();
		return 0;						// сообщение занесено в базу

	}
}
