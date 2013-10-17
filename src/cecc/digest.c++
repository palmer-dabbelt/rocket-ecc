#include "digest.h++"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Digest::Digest(std::string hex, int size)
{
    this->size = size;
    this->hex = hex;

    this->raw_bytes = new unsigned char[size / 8];
    {
        char *raw_bytes, *raw_hex;
        raw_bytes = (char *)this->raw_bytes;
        raw_hex = (char *)this->hex.c_str();

        for (int i = 0; i < (this->size / 8); i++) {
            unsigned int val;

            val = (*raw_hex) - '0';
            val <<= 8;
            raw_hex++;

            val += (*raw_hex) - '0';
            raw_hex++;

            *raw_bytes = val;
            raw_bytes++;
        }
    }
}

Digest::~Digest(void)
{
    delete[] this->raw_bytes;
}

int Digest::length(void) const
{
    return this->size;
}

const unsigned char *Digest::bytes(void) const
{
    return this->raw_bytes;
}
