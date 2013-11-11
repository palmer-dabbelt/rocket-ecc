#ifndef SIGNATURE_HXX
#define SIGNATURE_HXX

#include "bigint.h++"

#include <string>

class Signature
{
private:
    BigInt _r;
    BigInt _s;

public:
    /* Parses a signature from a pair of hex values. */
    Signature(std::string r_hex, std::string s_hex, int size);

    Signature(BigInt &r, BigInt &s);

    /* Obtains the two parameters. */
    std::string r(void) const;
    std::string s(void) const;
};

#endif
