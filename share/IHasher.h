/*
	Интерфейс для классов хеширования
*/
#pragma once
#include <cstddef>
namespace mychat {
	class IHasher
	{
	public:
		virtual ~IHasher() = default;
		virtual char* getHash(const char* message, size_t msize_bytes) = 0;
		virtual size_t getLenghtHash() = 0;
	};
}
