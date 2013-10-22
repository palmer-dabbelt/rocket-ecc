#ifndef DIGEST_HXX
#define DIGEST_HXX

#include "bigint.h++"

#include <string>
#include <stddef.h>
#include <unistd.h>

class Digest: public BigInt
{
public:
    Digest(std::string hex, int bit_length);

    /* Computes the DJB hash of this digest (I know it's akward to
     * compute a hash of a hash, but this is just a sanity check. */
    uint32_t djb_hash(void) const;
};

#endif
