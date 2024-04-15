/*
    Алгоритм шифрования SHA-1
*/

#pragma once
#include "IHasher.h"
#include <cstdint>
namespace mychat 
{
    class CypherSHA1 : public IHasher
    {
    private:
        using uint = uint32_t;
        // чтобы константы были одинаковыми для всех экземпляров этого класса, указываем их как static
        static const size_t one_block_size_bytes = 64;
        static const size_t one_block_size_uints = 16;
        static const size_t block_expend_size_uints = 80;
        static const size_t SHA1HASHLENGTHBYTES = 20;
        static const size_t SHA1HASHLENGTHUINTS = 5;
        using Block = uint*;
        using ExpendBlock = uint[block_expend_size_uints];

        const uint H[5] = {
            0x67452301,
            0xEFCDAB89,
            0x98BADCFE,
            0x10325476,
            0xC3D2E1F0
        }; // константы, согласно стандарту

        uint cycle_shift_left(uint val, int bit_count);
        uint bring_to_human_view(uint val);
    public:
        ~CypherSHA1() = default;
        // возвращает указатель на хеш - массив из пяти uint32_t
        char* getHash(const char* message, size_t msize_bytes) override;
        size_t getLenghtHash() override;
    };
}
