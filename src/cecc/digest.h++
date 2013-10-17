#ifndef DIGEST_HXX
#define DIGEST_HXX

#include <string>
#include <stddef.h>

class Digest
{
private:
    int size;
    std::string hex;
    unsigned char *raw_bytes;

public:
    /* Creates a new digest from a given hex value passed in as a
     * string. */
    Digest(std::string hex, int size);

    ~Digest();

    /* Returns the length of this digest. */
    int length(void) const;

    /* Returns the contents of this digest as represeted by a block of
     * memory. */
    const unsigned char *bytes(void) const;
};

#endif
