#include "public_key.h++"

PublicKey::PublicKey(std::string hex, int length)
{
    this->length = length;
    this->hex = hex;
}
