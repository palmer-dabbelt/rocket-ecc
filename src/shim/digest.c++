#include "digest.h++"

Digest::Digest(std::string hex, int bit_length)
    : BigInt(hex, bit_length)
{
}
