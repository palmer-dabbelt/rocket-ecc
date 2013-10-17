#ifndef PUBLIC_KEY_HXX
#define PUBILC_KEY_HXX

#include <string>

class PublicKey
{
public:
    int length;
    std::string hex;

public:
    PublicKey(std::string hex, int length);
};

#endif
