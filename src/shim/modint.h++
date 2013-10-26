#ifndef MODINT_HXX
#define MODINT_HXX

#include "bigint.h++"

/* ModInts are like BigInts but they're kept below some non
 * power-of-two mod all the time. */
class ModInt
{
private:
    BigInt _data;
    BigInt _mod;

public:
    /* These constructors are effectively the same as the BigInt
     * constructors but they contain an extra mod parameter. */
    ModInt(std::string hex, int bit_length, BigInt mod);
    ModInt(std::string hex, int offest, int bit_length, BigInt mod);
    ModInt(BigInt data, BigInt mod);

    /* Returns this integer as a hex string (the data, not the
     * modulus). */
    std::string hex(void) const { return _data.hex(); }
    const char *hex_cstr(void) const { return _data.hex_cstr(); }

    /* Returns the length of this interger (the data and the mod must
     * match). */
    int bit_length(void) const { return _data.bit_length(); }
    int byte_length(void) const { return _data.byte_length(); }

    /* Returns this integer as a byte string, not NUL terminated (the
     * data, not the mod). */
    const unsigned char *byte_str(void) const { return _data.byte_str(); }

    /* Here's a number of arithmatic operations that can be done on a
     * ModInt, all of which do their associated operation in modular
     * arithmetic. */
    friend ModInt operator+(const ModInt &a, const ModInt &b);
    friend ModInt operator-(const ModInt &a, const ModInt &b);
    friend ModInt operator*(const ModInt &a, const ModInt &b);

};

#endif
