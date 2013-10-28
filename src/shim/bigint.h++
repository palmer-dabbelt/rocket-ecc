#ifndef BIGINT_HXX
#define BIGINT_HXX

#include <string>
#include <stdint.h>

/* FIXME: This enforces a constant bit length. */
#ifndef BIGINT_MAX_BIT_LENGTH
#define BIGINT_MAX_BIT_LENGTH 512
#endif

/* This will only work for multiple of 64 bit lengths, but who cares! */
typedef uint64_t bigint_datum_t;
#define BIGINT_MAX_WORD_LENGTH \
    (BIGINT_MAX_BIT_LENGTH / (sizeof(bigint_datum_t) * 8))

typedef __uint128_t bigint_double_datum_t;

class BigInt
{
protected:
    bigint_datum_t _data[BIGINT_MAX_WORD_LENGTH];
    int _bit_length;
    bool _overflow;

public:
    /* Generates a new BigInt from a hex string. */
    BigInt(std::string hex, int bit_length);

    /* Generates a new BigInt from a section of a hex string, starting
     * at "offset" BITS (not characters), and of the length
     * "bit_length". */
    BigInt(std::string hex, int offest, int bit_length);

    /* A simple BigInt copy constructor. */
    BigInt(const BigInt &other);

    /* Generates a new BigInt from a regular integer, which can only
     * populate the least significant bit but otherwise is
     * acceptable. */
    BigInt(int value, int bit_length);

    /* Returns this integer as a hex string. */
    std::string hex(void) const;
    const char *hex_cstr(void) const;

    /* Returns the length of this interger. */
    int bit_length(void) const { return this->_bit_length; }
    int byte_length(void) const { return this->bit_length() / 8; }
    int word_length(void) const { return this->byte_length() / 8; }

    /* Returns this integer as a byte string, not NUL terminated. */
    const unsigned char *byte_str(void) const;

    /* Returns TRUE if there has been any overflow while computing
     * this integer, FALSE otherwise. */
    bool overflow(void) const { return _overflow; }
    std::string of_str(void) const { return _overflow ? "true" : "false"; }

    /* Allows for the manipulation of BigInt bit widths. */
    BigInt extend(int new_bit_length) const;
    BigInt extend2x(void) const { return extend(bit_length() * 2); }

    BigInt trunc(int new_bit_length) const;
    BigInt trunc2x(void) const { return trunc(bit_length() / 2); }
    friend BigInt trunc2x(const BigInt &i) { return i.trunc2x(); }

    /* This lets us easily check if the numbere is odd or even. */
    bool is_even(void) const { return (_data[word_length()-1] % 2) == 0; }
    bool is_odd(void) const { return !this->is_even(); }

    /* Here's a number of arithmatic operations that can be done on a
     * BigInt, all of which do their associated operation. */
    friend BigInt operator+(const BigInt &a, const BigInt &b);
    friend BigInt operator-(const BigInt &a, const BigInt &b);
    friend BigInt operator*(const BigInt &a, const BigInt &b);
    friend BigInt operator%(const BigInt &a, const BigInt &b);

    /* Some logical operators, which can be useful for many things
     * (including but not limited to some of the operations above). */
    BigInt operator~(void) const;
    BigInt operator<<(int i) const;
    BigInt operator>>(int i) const;

    /* Some comparison operators. */
    friend bool operator==(const BigInt &a, const BigInt &b);
    friend bool operator==(const BigInt &a, int b)
        { return a == BigInt(b, a.bit_length()); }
    friend bool operator==(int a, const BigInt &b)
        { return BigInt(a, b.bit_length()) == b; }

    friend bool operator!=(const BigInt &a, const BigInt &b)
        { return !(a == b); }
    friend bool operator!=(const BigInt &a, int b)
        { return a != BigInt(b, a.bit_length()); }
    friend bool operator!=(int a, const BigInt &b)
        { return BigInt(a, b.bit_length()) != b; }

    friend bool operator>(const BigInt &a, const BigInt &b);

    friend bool operator>=(const BigInt &a, const BigInt &b);

    friend bool operator<(const BigInt &a, const BigInt &b)
        { return !(a >= b); }

    friend bool operator<=(const BigInt &a, const BigInt &b)
        { return !(a > b); }
};

#endif
