#include "public_key.h++"

PublicKey::PublicKey(std::string hex, int bit_length)
    : Point(hex, bit_length)
{
}
