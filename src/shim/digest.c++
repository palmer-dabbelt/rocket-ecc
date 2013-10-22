#include "digest.h++"
#include <stdlib.h>

Digest::Digest(std::string hex, int bit_length)
    : BigInt(hex, bit_length)
{
}

uint32_t Digest::djb_hash(void) const
{
    uint32_t hash;
    const unsigned char *bytes;

    bytes = this->byte_str();

    hash = 5381;
    for (int i = 0; i < this->byte_length(); i++) {
        hash = hash * 33 ^ bytes[i];
    }

    free((void *)bytes);
    return hash;
}
