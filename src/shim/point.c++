#include "point.h++"

#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Point::Point(std::string hex, int bit_length)
    : _x(hex, 8             , bit_length),
      _y(hex, bit_length + 8, bit_length)
{
    assert(hex.length() == ((size_t)bit_length / 2) + 2);
}

std::string Point::x_hex(void) const
{
    return this->_x.hex();
}

std::string Point::y_hex(void) const
{
    return this->_y.hex();
}

const char *Point::hex_cstr(void) const
{
    char *out;

    asprintf(&out, "04%s%s", this->x_hex().c_str(), this->y_hex().c_str());

    return out;
}
