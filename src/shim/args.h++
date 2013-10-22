#ifndef ARGS_HXX
#define ARGS_HXX

#include "bigint.h++"
#include "curve.h++"
#include "digest.h++"
#include "public_key.h++"
#include "private_key.h++"

/* Parses the commandline argumens that are known to CECC. */
class Args
{
public:
    const Curve *curve;
    Digest *digest;
    PublicKey *public_key;
    PrivateKey *private_key;
    BigInt *rp;
    BigInt *kinv;
    BigInt *r;
    BigInt *s;

public:
    Args(int argc, char **argv);
};

#endif
