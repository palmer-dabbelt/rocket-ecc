#include "curve.h++"

#include <string.h>

Curve::Curve(std::string name)
{
    /* This is essentially just a giant lookup table that decodes the
     * key size. */
    if (name.compare("p256k1") == 0) {
        this->type = TYPE_P_256_K_1;
    } else if (name.compare("p521r1") == 0) {
        this->type = TYPE_P_521_R_1;
    } else {
        throw InvalidArgument("Unable to parse curve parameter");
    }
}

int Curve::size(void) const
{
    switch (this->type) {
    case TYPE_P_256_K_1:
        return 256;
    case TYPE_P_521_R_1:
        return 512;
    }

    return -1;
}
