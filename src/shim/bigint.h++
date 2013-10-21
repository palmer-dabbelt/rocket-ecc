#ifndef BIGINT_HXX
#define BIGINT_HXX

#include <string>

class BigInt
{
protected:
    int _bit_length;
    std::string _hex;
    unsigned char *_bytes;

public:
    BigInt(std::string hex, int bit_length);

    /* Returns this integer as a hex string. */
    std::string hex(void) const;
    const char *hex_cstr(void) const;

    /* Returns the length of this interger. */
    int bit_length(void) const;
    int byte_length(void) const;

    /* Returns this integer as a byte string, not NUL terminated. */
    const unsigned char *byte_str(void) const;
};

#endif
