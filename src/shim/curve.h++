#ifndef CURVE_HXX
#define CURVE_HXX

#include "invalid_argument.h++"

#include <string>

class Curve
{
public:
    /* We only support a fixed set of curves, the list lives here. */
    enum Type {
        TYPE_P_256_K_1,
        TYPE_P_521_R_1
    };

private:
    /* Enumerates what sort of curve this is. */
    enum Type _type;

public:
    /* Generates a new curve, given the canonical name of that curve
     * according to NIST.  We default to 256-bit keys, and only
     * support prime keys as that's what we'll be accelerating in
     * hardware. */
    Curve(std::string name = "p256k1");

#ifdef HAVE_OPENSSL
    /* Maps this curve to OpenSSL's internal curve index. */
    int openssl_name(void) const;
#endif

    /* Returns the size of this curve, which is the actual bit size
     * (not the security parameter). */
    int bit_length(void) const;
};

#endif
