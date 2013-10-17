#include "private_key.h++"

PrivateKey::PrivateKey(std::string hex, int length)
{
    this->length = length;
    this->hex = hex;
}
