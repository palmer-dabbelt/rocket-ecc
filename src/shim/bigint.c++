#include "bigint.h++"
#include <assert.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int hex2int(unsigned char c)
{
    switch (c) {
    case '0': return 0;
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    case '8': return 8;
    case '9': return 9;
    case 'a': return 10;
    case 'b': return 11;
    case 'c': return 12;
    case 'd': return 13;
    case 'e': return 14;
    case 'f': return 15;
    case 'A': return 10;
    case 'B': return 11;
    case 'C': return 12;
    case 'D': return 13;
    case 'E': return 14;
    case 'F': return 15;
    }

    return -1;
}

BigInt::BigInt(std::string hex,
               int bit_length __attribute__((unused)))
{
    const char *str;

    str = hex.c_str();

    assert(BIGINT_BIT_LENGTH == 256);
    sscanf(str, "%016lx%016lx%016lx%016lx",
           this->_data + 0,
           this->_data + 1,
           this->_data + 2,
           this->_data + 3);
}

BigInt::BigInt(std::string hex, int offset,
               int bit_length __attribute__((unused)))
{
    const char *str;

    str = hex.c_str() + (offset / 4);

    assert(BIGINT_BIT_LENGTH == 256);
    sscanf(str, "%016lx%016lx%016lx%016lx",
           this->_data + 0,
           this->_data + 1,
           this->_data + 2,
           this->_data + 3);
}

std::string BigInt::hex(void) const
{
    char buf[1024];

    snprintf(buf, 1024, "%016lX%016lX%016lX%016lX",
             this->_data[0],
             this->_data[1],
             this->_data[2],
             this->_data[3]);

    return buf;
}

const char *BigInt::hex_cstr(void) const
{
    return strdup(this->hex().c_str());
}

int BigInt::bit_length(void) const
{
    return BIGINT_BIT_LENGTH;
}

int BigInt::byte_length(void) const
{
    return BIGINT_BIT_LENGTH / 8;
}

const unsigned char *BigInt::byte_str(void) const
{
    const char *hex;
    unsigned char *bytes, *bytes_out;

    hex = this->hex_cstr();
    bytes = (unsigned char *)malloc((size_t)this->byte_length());
    bytes_out = bytes;

    for (int i = 0; i < this->byte_length(); i++) {
        unsigned int val;

        val = hex2int(*hex);
        val <<= 4;
        hex++;

        val += hex2int(*hex);
        hex++;

        *bytes = val;
        bytes++;

        fprintf(stderr, "byte[%d] = %d\n", i, (unsigned char)val);
    }

    return bytes_out;
}
