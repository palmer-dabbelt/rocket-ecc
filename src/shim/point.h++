#ifndef POINT_HXX
#define POINT_HXX

#include "curve.h++"
#include "modint.h++"

#include <string>

class Point
{
protected:
    const Curve *_c;
    ModInt _x;
    ModInt _y;

public:
    /* This constructs a new EC point from a single long string.  Here
     * "bit_length" is actually the length of a single int in the
     * point. */
    Point(std::string hex, const Curve *c);

    /* Simply returns the components of this point. */
    ModInt x(void) const { return _x; }
    ModInt y(void) const { return _y; }

    /* Returns each integer as a string. */
    std::string x_hex(void) const { return _x.hex(); }
    const char *x_hex_cstr(void) const { return _x.hex_cstr(); }

    std::string y_hex(void) const { return _y.hex(); }
    const char *y_hex_cstr(void) const { return _y.hex_cstr(); }

    /* Returns the pair of integers joined as a hex string, or a a C
     * string. */
    std::string hex_str(void) const;
    const char *hex_cstr(void) const;

    /* These arithmatic operators compute the geometric definition of
     * elliptic curve field operations. */
    friend Point operator+(const Point &a, const Point &b);
};

#endif
