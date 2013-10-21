#include "bigint.h++"

BigInt::BigInt(void)
{
    this->_bit_length = -1;
}

BigInt::BigInt(std::string hex, int bit_length)
{
    this->_hex = hex;
    this->_bit_length = bit_length;
}

std::string BigInt::hex(void) const
{
    return this->_hex;
}

const char *BigInt::hex_cstr(void) const
{
    return this->_hex.c_str();
}
