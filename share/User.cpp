/*
	Класс участник чата
*/

#include "User.h"
#include "opcodes.h"
#include <iostream>


namespace mychat {
	User::User(const std::string& name, const std::string& pass) : user_{ name, pass }
	{}

	// <user_name:string><messageSeparator:char><hashLenght:string><hash:string>
	User::User(char* userData)
	{
		while (*userData != messageSeparator) {
			user_.name.push_back(*userData);
			userData += 1;
		}

		userData += 1;
		std::string hashSizeStr(userData, 2);
		int hashSize = std::stoi(hashSizeStr);

		userData += 2;
		while (hashSize) {
			user_.password.push_back(*userData);
			userData += 1;
			--hashSize;
		}
	}

	User::~User()
	{
		std::cout << "~User()\n";
	}

	const std::string* User::getName()
	{
		return &user_.name;
	}
	const std::string* User::getPassword()
	{
		return &user_.password;
	}

	void User::setName(const std::string& str)
	{
		user_.name = str;
	}
	void User::setPassword(const std::string& str)
	{
		user_.password = str;
	}
}

