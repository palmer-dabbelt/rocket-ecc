#include "ecdsa.h++"
#include "point.h++"
#include <assert.h>
#include <stdio.h>

#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

Signature *ecdsa_asign(const Digest &d_bi,
                       const BigInt &kinv_bi,
                       const BigInt &rp,
                       const PrivateKey &key_bi,
                       const Curve &c)
{
    /* Sets up the ECDSA computation. */
    ModInt d    = c.order(d_bi);
    ModInt k    = c.order_invert(kinv_bi);
    ModInt kinv = c.order(kinv_bi);
    Point  G    = Point(c.G_x(), c.G_y(), &c);
    ModInt key  = c.order(key_bi);

    /* OpenSSL has a fast-path for finding X without actually doing a
     * point multiplication -- this certianly seems like cheating to
     * me! */
#ifdef FAST_OPENSSL_KGX
    ModInt x = c.field(rp);
#else
    Point kG = k * G;
    ModInt x = kG.x();
#endif
    ModInt r = c.order(x);

    ModInt s  = kinv * (d + r * key);

    BigInt rbi(r.data());
    BigInt sbi(s.data());
    return new Signature(rbi, sbi);
}
