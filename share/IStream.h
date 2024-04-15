/*
	Интерфейс для классов приёма\передачи
*/
#pragma once
#include <cstddef>
namespace mychat {
	class IStream
	{
	public:

		virtual ~IStream() = default;

		virtual int sending(const char* str, std::size_t str_lenght) = 0;
		virtual int receiving() = 0;
		virtual size_t getResponseLenght() = 0;
		virtual char* getResponse() = 0;
	};
}
