#include "point.h++"

#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Point::Point(std::string hex, const Curve *c)
    : _x(hex, 8                  , c->bit_length(), c->q()),
      _y(hex, c->bit_length() + 8, c->bit_length(), c->q())
{
    this->_c = c;
    assert(hex.length() == ((size_t)c->bit_length() / 2) + 2);
}

const char *Point::hex_cstr(void) const
{
    char *out;
    int r;

    r = asprintf(&out, "04%s%s", this->x_hex().c_str(), this->y_hex().c_str());
    if (r <= 0)
        abort();

    return out;
}
