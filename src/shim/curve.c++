#include "curve.h++"

#include <string.h>

#ifdef HAVE_OPENSSL
#include <openssl/obj_mac.h>
#endif

/* The known curves are allocated staticly. */
static Curve *get_p256k1(void);
static Curve *get_certicom23(void);
static Curve *get_certicom17(void);

const Curve *Curve::lookup_curve(std::string name)
{
    /* This is essentially just a giant lookup table that decodes the
     * key size. */
    if (name.compare("p256k1") == 0) {
        return get_p256k1();
    } else if (name.compare("certicom23") == 0) {
        return get_certicom23();
    } else if (name.compare("certicom17") == 0) {
        return get_certicom17();
    } else {
        throw InvalidArgument("Unable to parse curve parameter");
    }
}

Curve::Curve(std::string p_hex,
             std::string a_hex,
             std::string b_hex,
             std::string x_G_hex,
             std::string y_G_hex,
             std::string q_hex,
             int bit_length, enum Type type)
    : _p(p_hex, bit_length),
      _a(a_hex, bit_length),
      _b(b_hex, bit_length),
      _x_G(x_G_hex, bit_length),
      _y_G(y_G_hex, bit_length),
      _q(q_hex, bit_length)
{
    this->_bit_length = bit_length;
    this->_type = type;
}

#ifdef HAVE_OPENSSL
int Curve::openssl_name(void) const
{
    switch (this->_type) {
    case TYPE_P_256_K_1:
        return NID_secp256k1;
    case TYPE_CERTICOM23:
    case TYPE_CERTICOM17:
        return -1;
    }

    /* This should never get here, but I guess the C++ compiler
     * doesn't detect that?  It's odd, because I belive C will... */
    return -1;
}
#endif

Curve *get_p256k1(void)
{
    static Curve *p256k1 = NULL;

    if (p256k1 == NULL) {
        p256k1 = new Curve(
            "ffffffff00000001000000000000000000000000ffffffffffffffffffffffff",
            "ffffffff00000001000000000000000000000000fffffffffffffffffffffffc",
            "5ac635d8aa3a93e7b3ebbd55769886bc651d06b0cc53b0f63bce3c3e27d2604b",
            "6b17d1f2e12c4247f8bce6e563a440f277037d812deb33a0f4a13945d898c296",
            "4fe342e2fe1a7f9b8ee7eb4a7c0f9e162bce33576b315ececbb6406837bf51f5",
            "ffffffff00000000ffffffffffffffffbce6faada7179e84f3b9cac2fc632551",
            256, Curve::TYPE_P_256_K_1);
    }

    return p256k1;
}

Curve *get_certicom23(void)
{
    static Curve *certicom23 = NULL;

    if (certicom23 == NULL) {
        certicom23 = new Curve(
            "0000000000000000000000000000000000000000000000000000000000000017",
            "0000000000000000000000000000000000000000000000000000000000000001",
            "0000000000000000000000000000000000000000000000000000000000000000",
            "0000000000000000000000000000000000000000000000000000000000000000",
            "0000000000000000000000000000000000000000000000000000000000000000",
            "0000000000000000000000000000000000000000000000000000000000000017",
            256, Curve::TYPE_CERTICOM23);
    }

    return certicom23;
}

Curve *get_certicom17(void)
{
    static Curve *certicom17 = NULL;

    if (certicom17 == NULL) {
        certicom17 = new Curve(
            "0000000000000000000000000000000000000000000000000000000000000011",
            "0000000000000000000000000000000000000000000000000000000000000001",
            "0000000000000000000000000000000000000000000000000000000000000000",
            "0000000000000000000000000000000000000000000000000000000000000000",
            "0000000000000000000000000000000000000000000000000000000000000000",
            "0000000000000000000000000000000000000000000000000000000000000011",
            256, Curve::TYPE_CERTICOM23);
    }

    return certicom17;
}
