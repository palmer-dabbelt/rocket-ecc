#include "private_key.h++"

PrivateKey::PrivateKey(std::string hex, int bit_length)
    : BigInt(hex, bit_length)
{
}
