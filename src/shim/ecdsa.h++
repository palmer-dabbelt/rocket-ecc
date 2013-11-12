#ifndef ECDSA_H
#define ECDSA_H

#include "curve.h++"
#include "digest.h++"
#include "modint.h++"
#include "private_key.h++"
#include "signature.h++"

/* This contains the top-level ECDSA signature algorithm. */
Signature *ecdsa_asign(const Digest &d,
                       const BigInt &kinv,
                       const BigInt &rp,
                       const PrivateKey &k,
                       const Curve &curve);

#endif
