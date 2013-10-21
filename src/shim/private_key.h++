#ifndef PRIVATE_KEY_HXX
#define PRIVATE_KEY_HXX

#include "bigint.h++"

#include <string>

class PrivateKey: public BigInt
{
public:
    PrivateKey(std::string hex, int bit_length);
};

#endif
