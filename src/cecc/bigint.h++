#ifndef BIGINT_HXX
#define BIGINT_HXX

#include <string>

class BigInt
{
public:
    int length;
    std::string hex;

public:
    BigInt(std::string hex, int length);
};

#endif
