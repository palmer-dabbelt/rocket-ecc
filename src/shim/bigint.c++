#include "bigint.h++"
#include <iostream>
#include <stdlib.h>
#include <string.h>

BigInt::BigInt(std::string hex, int bit_length)
{
    this->initialize(hex, bit_length);
}

BigInt::BigInt(std::string hex, int offset, int bit_length)
{
    const char *str;
    char *str_duped;

    str = hex.c_str();
    str += (offset / 4);

    str_duped = strndup(str, (bit_length / 4) + 1);

    initialize(str_duped, bit_length);

    free(str_duped);
}

std::string BigInt::hex(void) const
{
    return this->_hex;
}

const char *BigInt::hex_cstr(void) const
{
    return this->_hex.c_str();
}

int BigInt::bit_length(void) const
{
    return this->_bit_length;
}

int BigInt::byte_length(void) const
{
    return this->_bit_length / 8;
}

const unsigned char *BigInt::byte_str(void) const
{
    return this->_bytes;
}

void BigInt::initialize(std::string hex, int bit_length)
{
    this->_hex = hex;
    this->_bit_length = bit_length;

    this->_bytes = new unsigned char[bit_length / 8];
    {
        char *raw_bytes, *raw_hex;
        raw_bytes = (char *)this->_bytes;
        raw_hex = (char *)this->_hex.c_str();

        for (int i = 0; i < (bit_length / 8); i++) {
            unsigned int val;

            val = (*raw_hex) - '0';
            val <<= 8;
            raw_hex++;

            val += (*raw_hex) - '0';
            raw_hex++;

            *raw_bytes = val;
            raw_bytes++;
        }
    }
}
