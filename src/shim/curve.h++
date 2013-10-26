#ifndef CURVE_HXX
#define CURVE_HXX

#include "bigint.h++"
#include "invalid_argument.h++"

#include <string>

class Curve
{
public:
    enum Type
    {
        TYPE_P_256_K_1
    };

private:
    /* Enumerates what sort of curve this is. */
    enum Type _type;
    int _bit_length;
    BigInt _p;
    BigInt _a;
    BigInt _b;
    BigInt _x_G;
    BigInt _y_G;
    BigInt _q;

public:
    /* Generates a new curve, given the canonical name of that curve
     * according to NIST.  We default to 256-bit keys, and only
     * support prime keys as that's what we'll be accelerating in
     * hardware. */
    static const Curve *lookup_curve(std::string name);

    /* Fills out a curve given some parameters about it.  This is
     * probably not the constructor you're looking for... */
    Curve(std::string p_hex,
          std::string a_hex,
          std::string b_hex,
          std::string x_G_hex,
          std::string y_G_hex,
          std::string q_hex,
          int bit_length, enum Type type);

#ifdef HAVE_OPENSSL
    /* Maps this curve to OpenSSL's internal curve index. */
    int openssl_name(void) const;
#endif

    /* Returns the size of this curve, which is the actual bit size
     * (not the security parameter). */
    int bit_length(void) const { return _bit_length; }

    /* The parameters of this curve, as defined by NIST. */
    BigInt p(void) const { return _p; }
    BigInt a(void) const { return _a; }
    BigInt b(void) const { return _b; }
    BigInt x_G(void) const { return _x_G; }
    BigInt y_G(void) const { return _y_G; }
    BigInt q(void) const { return _q; }

};

#endif
