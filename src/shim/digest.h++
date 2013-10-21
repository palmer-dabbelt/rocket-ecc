#ifndef DIGEST_HXX
#define DIGEST_HXX

#include "bigint.h++"

#include <string>
#include <stddef.h>

class Digest: public BigInt
{
public:
    Digest(std::string hex, int bit_length);

};

#endif
