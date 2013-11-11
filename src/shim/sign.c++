#include "args.h++"
#include "ecdsa.h++"
#include <iostream>

int main(int argc, char **argv)
{
    const Args *args;
    const PrivateKey *key;
    const BigInt *kinv;
    const BigInt *rp;
    const Digest *digest;
    const Curve *curve;
    const Signature *sig;

    /* Here we simply parse the command-line arguments. */
    args = new Args(argc, argv);

    /* The argument list essentially does all the signing for us, here
     * we simply pull out that data. */
    key = args->private_key;
    kinv = args->kinv;
    rp = args->rp;
    digest = args->digest;
    curve = args->curve;

    /* Here's where we actually produce a signature. */
    sig = ecdsa_asign(*digest, *kinv, *rp, *key, *curve);

    std::cout << "--r " << sig->r() << "\n";
    std::cout << "--s " << sig->s() << "\n";

    /* Cleans up after our own allocations. */
    delete sig;
    delete args;

    return 0;
}
