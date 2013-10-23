#ifndef POINT_HXX
#define POINT_HXX

#include "bigint.h++"
#include "curve.h++"

#include <string>

class Point
{
protected:
    const Curve *_c;
    BigInt _x;
    BigInt _y;

public:
    /* This constructs a new EC point from a single long string.  Here
     * "bit_length" is actually the length of a single int in the
     * point. */
    Point(std::string hex, const Curve *c);

    /* Returns each integer as a string. */
    std::string x_hex(void) const;
    const char *x_hex_cstr(void) const;

    std::string y_hex(void) const;
    const char *y_hex_cstr(void) const;

    /* Returns the pair of integers joined as a hex string, or a a C
     * string. */
    std::string hex_str(void) const;
    const char *hex_cstr(void) const;
};

#endif
