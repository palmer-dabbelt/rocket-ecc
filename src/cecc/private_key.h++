#ifndef PRIVATE_KEY_HXX
#define PRIVATE_KEY_HXX

#include <string>

class PrivateKey
{
public:
    int length;
    std::string hex;

public:
    PrivateKey(std::string hex, int length);
};

#endif
