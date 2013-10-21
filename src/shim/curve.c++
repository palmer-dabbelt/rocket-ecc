#include "curve.h++"

#include <string.h>

#ifdef HAVE_OPENSSL
#include <openssl/obj_mac.h>
#endif

Curve::Curve(std::string name)
{
    /* This is essentially just a giant lookup table that decodes the
     * key size. */
    if (name.compare("p256k1") == 0) {
        this->_type = TYPE_P_256_K_1;
    } else if (name.compare("p521r1") == 0) {
        this->_type = TYPE_P_521_R_1;
    } else {
        throw InvalidArgument("Unable to parse curve parameter");
    }
}

int Curve::bit_length(void) const
{
    switch (this->_type) {
    case TYPE_P_256_K_1:
        return 256;
    case TYPE_P_521_R_1:
        return 512;
    }

    return -1;
}


#ifdef HAVE_OPENSSL
int Curve::openssl_name(void) const
{
    switch (this->_type) {
    case TYPE_P_256_K_1:
        return NID_secp256k1;
    case TYPE_P_521_R_1:
        return NID_secp521r1;
    }

    /* This should never get here, but I guess the C++ compiler
     * doesn't detect that?  It's odd, because I belive C will... */
    return -1;
}
#endif
