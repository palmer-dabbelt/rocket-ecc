#ifndef BIGINT_HXX
#define BIGINT_HXX

#include <string>

class BigInt
{
private:
    int _bit_length;
    std::string _hex;

public:
    BigInt(void);

    BigInt(std::string hex, int bit_length);

    /* Returns this integer as a hex string. */
    std::string hex(void) const;
    const char *hex_cstr(void) const;
};

#endif
