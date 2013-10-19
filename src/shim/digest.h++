#ifndef DIGEST_HXX
#define DIGEST_HXX

#include <string>
#include <stddef.h>

class Digest
{
private:
    int _bit_length;
    std::string _hex;
    unsigned char *_bytes;

public:
    /* Creates a new digest from a given hex value passed in as a
     * string. */
    Digest(std::string hex, int bit_length);

    ~Digest();

    /* Returns the length of this digest. */
    int byte_length(void) const;
    int bit_length(void) const;

    /* Returns the contents of this digest as represeted by a block of
     * memory. */
    const unsigned char *bytes(void) const;
};

#endif
