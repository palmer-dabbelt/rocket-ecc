#ifndef POINT_HXX
#define POINT_HXX

#include "curve.h++"
#include "modint.h++"

#include <string>

class Point
{
protected:
    const Curve *_c;
    const ModInt _x;
    const ModInt _y;

public:
    /* This constructs a new EC point from a single long string.  The
     * length of the string must be exactly twice the length of the
     * curve. */
    Point(std::string hex, const Curve *c);

    /* Creates a point from two ModInts, each of which must be exactly
     * the length required by the curve. */
    Point(const ModInt &x, const ModInt &y, const Curve *c);

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
    friend Point operator+(const Point &P, const Point &Q);
};

#endif
