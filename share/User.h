/*
	Класс участник чата 
*/
#pragma once
#include <string>

namespace mychat {
	class User
	{
		struct UserData {
			std::string name;
			std::string password;
		} user_;

	public:
		User() = default;
		User(const std::string& name, const std::string& password);
		User(char* userData);
		~User();

		const std::string* getName();
		const std::string* getPassword();

		void setName(const std::string& str);
		void setPassword(const std::string& str);
	};
}
