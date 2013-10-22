#ifndef BIGINT_HXX
#define BIGINT_HXX

#include <string>
#include <stdint.h>

/* FIXME: This enforces a constant bit length. */
#ifndef BIGINT_BIT_LENGTH
#define BIGINT_BIT_LENGTH 256
#endif

/* This will only work for multiple of 64 bit lengths, but who cares! */
typedef uint64_t bigint_datum_t;
#define BIGINT_WORD_LENGTH (BIGINT_BIT_LENGTH / (sizeof(bigint_datum_t) * 8))

class BigInt
{
protected:
    bigint_datum_t _data[BIGINT_WORD_LENGTH];

public:
    /* Generates a new BigInt from a hex string. */
    BigInt(std::string hex, int bit_length);

    /* Generates a new BigInt from a section of a hex string, starting
     * at "offset" BITS (not characters), and of the length
     * "bit_length". */
    BigInt(std::string hex, int offest, int bit_length);

    /* Generates a new BigInt from a regular integer, which can only
     * populate the least significant bit but otherwise is
     * acceptable. */
    BigInt(int value);

    /* Returns this integer as a hex string. */
    std::string hex(void) const;
    const char *hex_cstr(void) const;

    /* Returns the length of this interger. */
    int bit_length(void) const;
    int byte_length(void) const;

    /* Returns this integer as a byte string, not NUL terminated. */
    const unsigned char *byte_str(void) const;

    /* Here's a number of arithmatic operations that can be done on a
     * BigInt, all of which do their associated operation. */
    friend BigInt operator+(const BigInt &a, const BigInt &b);
    friend BigInt operator*(const BigInt &a, const BigInt &b);
};

#endif
