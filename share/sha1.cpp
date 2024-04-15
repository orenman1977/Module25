/*
    Алгоритм шифрования SHA-1
*/

#include "sha1.h"
#include <cstring>
#include <iostream>

namespace mychat {
    CypherSHA1::uint CypherSHA1::cycle_shift_left(uint val, int bit_count) {
        return (val << bit_count | val >> (32 - bit_count));
    }

    // обмен слов в 32-разрядном int
    CypherSHA1::uint CypherSHA1::bring_to_human_view(uint val) {
        return  ((val & 0x000000FF) << 24) |
            ((val & 0x0000FF00) << 8) |
            ((val & 0x00FF0000) >> 8) |
            ((val & 0xFF000000) >> 24);
    }

    char* CypherSHA1::getHash(const char* message, size_t msize_bytes) {
        //инициализация
        uint A = H[0];
        uint B = H[1];
        uint C = H[2];
        uint D = H[3];
        uint E = H[4];

        // подсчет целого числа блоков
        size_t totalBlockCount = msize_bytes / one_block_size_bytes;

        // подсчет, сколько байт нужно, чтобы дополнить последний блок
        size_t needAdditionalBytes =
            one_block_size_bytes - (msize_bytes - totalBlockCount * one_block_size_bytes);

        if (needAdditionalBytes < 8) {
            totalBlockCount += 2;
            needAdditionalBytes += one_block_size_bytes;
        }
        else {
            totalBlockCount += 1;
        }

        // размер дополненного по всем правилам сообщения
        size_t extendedMessageSize = msize_bytes + needAdditionalBytes;

        // выделяем новый буфер и копируем в него исходный
        unsigned char* newMessage = new unsigned char[extendedMessageSize];
        memcpy(newMessage, message, msize_bytes);

        // первый бит ставим '1', остальные обнуляем
        newMessage[msize_bytes] = 0x80;
        memset(newMessage + msize_bytes + 1, 0, needAdditionalBytes - 1);

        // задаем длину исходного сообщения в битах
        uint* ptr_to_size = (uint*)(newMessage + extendedMessageSize - 4);
        *ptr_to_size = bring_to_human_view((uint)msize_bytes * 8);

        ExpendBlock exp_block{};
        //раунды поехали
        for (size_t i = 0; i < totalBlockCount; i++) {

            // берем текущий блок и дополняем его
            unsigned char* cur_p = newMessage + one_block_size_bytes * i;
            Block block = (Block)cur_p;

            // первые 16 4байтовых чисел
            for (int j = 0; j < one_block_size_uints; j++) {
                exp_block[j] = bring_to_human_view(block[j]);
            }
            // следующие 64...
            for (int j = one_block_size_uints; j < block_expend_size_uints; j++) {
                exp_block[j] =
                    exp_block[j - 3] ^
                    exp_block[j - 8] ^
                    exp_block[j - 14] ^
                    exp_block[j - 16];
                exp_block[j] = cycle_shift_left(exp_block[j], 1);
            }

            // инициализация 
            uint a = H[0];
            uint b = H[1];
            uint c = H[2];
            uint d = H[3];
            uint e = H[4];

            // пересчитываем
            for (int j = 0; j < block_expend_size_uints; j++) {
                uint f;
                uint k;
                // в зависимости от раунда считаем по-разному
                if (j < 20) {
                    f = (b & c) | ((~b) & d);
                    k = 0x5A827999;
                }
                else if (j < 40) {
                    f = b ^ c ^ d;
                    k = 0x6ED9EBA1;
                }
                else if (j < 60) {
                    f = (b & c) | (b & d) | (c & d);
                    k = 0x8F1BBCDC;
                }
                else {
                    f = b ^ c ^ d;
                    k = 0xCA62C1D6;
                }

                // перемешивание
                uint temp = cycle_shift_left(a, 5) + f + e + k + exp_block[j];
                e = d;
                d = c;
                c = cycle_shift_left(b, 30);
                b = a;
                a = temp;
            }
            // пересчитываем
            A = A + a;
            B = B + b;
            C = C + c;
            D = D + d;
            E = E + e;
        }

        // A,B,C,D,E являются выходными 32б составляющими посчитанного хэша
        char* digest = new char[SHA1HASHLENGTHBYTES];
        uint* pointer = (uint*)digest;
        pointer[0] = A;
        pointer[1] = B;
        pointer[2] = C;
        pointer[3] = D;
        pointer[4] = E;

        // чистим за собой
        delete[] newMessage;
        return digest;
    }

    size_t CypherSHA1::getLenghtHash()
    {
        return SHA1HASHLENGTHBYTES;
    }
}
