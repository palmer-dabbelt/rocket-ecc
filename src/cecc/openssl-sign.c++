#include "args.h++"
#include "signature.h++"

#include <iostream>
#include <openssl/ec.h>
#include <openssl/ecdsa.h>
#include <openssl/ssl.h>

int main(int argc, char **argv)
{
    Args *args;
    EC_GROUP *group;
    EC_KEY *key;
    ECDSA_SIG *sig;
    Signature *signature;

    /* Before touching anything we need to initialize OpenSSL. */
    SSL_library_init();

    /* Here we simply parse the command-line arguments. */
    args = new Args(argc, argv);

    /* Generates a new elliptic curve given the name the
     * commandline. */
    group = EC_GROUP_new_by_curve_name(args->curve->openssl_name());

    /* Allocates a new key and sets it to some known values */
    key = EC_KEY_new_by_curve_name(args->curve->openssl_name());
    if (key == NULL) {
        std::cerr << "Unable to allocate key structure\n";
        exit(1);
    }

    /* FIXME: Actually generates the key instead of reading it in. */
    if (EC_KEY_generate_key(key) != 1) {
        std::cerr << "Unable to generate keypair\n";
        exit(1);
    }

    /* Here's where we actually do the signature. */
    sig = ECDSA_do_sign(args->digest->bytes(), args->digest->length(), key);
    if (sig == NULL) {
        std::cerr << "Unable to sign digest\n";
        exit(1);
    }

    /* Finally convert the signature into a more standardized
     * format. */
    signature = new Signature(BN_bn2hex(sig->r),
                              BN_bn2hex(sig->s),
                              i2d_ECDSA_SIG(sig, NULL));

    std::cout << "--r " << signature->r() << "\n";
    std::cout << "--s " << signature->s() << "\n";

    /* Cleans up the OpenSSL context. */
    ECDSA_SIG_free(sig);
    EC_KEY_free(key);
    EC_GROUP_free(group);

    /* Cleans up after our own allocations. */
    delete signature;
    delete args;

    return 0;
}
