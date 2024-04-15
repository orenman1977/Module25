/*
	коды операций
*/
#pragma once
namespace mychat {
	enum class myCode : char
	{
		// ответы сервера
		good,
		bad,
		user_exists,
		end_of_data_transmission,

		// запросы клиента
		login,
		registration,
		shareMessage,
		privatMessage,

		// разделитель
		messageSeparator
	};

	constexpr char good = static_cast<char>(myCode::good);
	constexpr char bad = static_cast<char>(myCode::bad);
	constexpr char user_exists = static_cast<char>(myCode::user_exists);
	constexpr char end_of_data_transmission = static_cast<char>(myCode::end_of_data_transmission);
	constexpr char login = static_cast<char>(myCode::login);
	constexpr char registration = static_cast<char>(myCode::registration);
	constexpr char shareMessage = static_cast<char>(myCode::shareMessage);
	constexpr char privatMessage = static_cast<char>(myCode::privatMessage);
	constexpr char messageSeparator = static_cast<char>(myCode::messageSeparator);
}
