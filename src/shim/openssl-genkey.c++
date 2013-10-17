#include "args.h++"

#include <iostream>
#include <openssl/ec.h>
#include <openssl/ecdsa.h>
#include <openssl/bn.h>

int main(int argc, char **argv)
{
    Args *args;
    EC_GROUP *group;
    EC_KEY *key;
    const EC_POINT *pubkey;
    char *pubkey_str;
    const BIGNUM *privkey;
    point_conversion_form_t form;
    BIGNUM *rp;
    BIGNUM *kinv;

    /* Here we simply parse the command-line arguments. */
    args = new Args(argc, argv);

    /* Generates a new elliptic curve given the name the
     * commandline. */
    group = EC_GROUP_new_by_curve_name(args->curve->openssl_name());
    form = EC_GROUP_get_point_conversion_form(group);

    /* Allocates a new key and sets it to some known values */
    key = EC_KEY_new_by_curve_name(args->curve->openssl_name());
    if (key == NULL) {
        std::cerr << "Unable to allocate key structure\n";
        exit(1);
    }

    /* Generate a random key. */
    if (EC_KEY_generate_key(key) != 1) {
        std::cerr << "Unable to generate keypair\n";
        exit(1);
    }

    /* Prints out the pubilc and private keys. */
    pubkey = EC_KEY_get0_public_key(key);
    {
        BN_CTX *ctx;

        ctx = BN_CTX_new();
        pubkey_str = EC_POINT_point2hex(group, pubkey, form, ctx);
        BN_CTX_free(ctx);
    }
    std::cout << "--pubkey " << pubkey_str << "\n";

    privkey = EC_KEY_get0_private_key(key);
    std::cout << "--privkey " << BN_bn2hex(privkey) << "\n";

    /* Generates a new random set of ECDSA signing parameters. */
    {
        BN_CTX *ctx;

        ctx = BN_CTX_new();

        rp = NULL;
        kinv = NULL;
        ECDSA_sign_setup(key, ctx, &rp, &kinv);

        std::cout << "--rp " << BN_bn2hex(rp) << "\n";
        std::cout << "--kinv " << BN_bn2hex(kinv) << "\n";

        BN_CTX_free(ctx);
    }

    /* Cleans up the OpenSSL context. */
    EC_KEY_free(key);
    EC_GROUP_free(group);

    /* Cleans up after our own allocations. */
    delete args;
}
