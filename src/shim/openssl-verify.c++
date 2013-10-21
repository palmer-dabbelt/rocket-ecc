#include "args.h++"
#include "signature.h++"

#include <iostream>
#include <openssl/ec.h>
#include <openssl/ecdsa.h>

int main(int argc, char **argv)
{
    Args *args;
    EC_GROUP *group;
    EC_KEY *key;
    ECDSA_SIG *sig;
    int verified;

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

    /* Set the key to something known so we keep getting the same
     * signature every time, allowing the test harness to actually
     * run. */
    {
        BN_CTX *ctx;
        EC_POINT *pubkey;
        const char *pubkey_str;

        pubkey = EC_POINT_new(group);
        pubkey_str = args->public_key->hex_cstr();

        ctx = BN_CTX_new();
        pubkey = EC_POINT_hex2point(group, pubkey_str, pubkey, ctx);
        EC_KEY_set_public_key(key, pubkey);
        BN_CTX_free(ctx);
    }

    /* FIXME: We probably shouldn't need the private key... righ? */
    {
        BIGNUM *privkey;
        const char *privkey_str;
        
        privkey_str = args->private_key->hex_cstr();
        privkey = NULL;
        BN_hex2bn(&privkey, privkey_str);
        EC_KEY_set_private_key(key, privkey);
    }

    /* Load up the signature from the commandline arguments. */
    sig = ECDSA_SIG_new();
    BN_hex2bn(&sig->r, args->r->hex_cstr());
    BN_hex2bn(&sig->s, args->s->hex_cstr());

    /* Here's where we actually do the verification. */
    verified = ECDSA_do_verify(args->digest->byte_str(),
                               args->digest->byte_length(),
                               sig, key);

    if (verified) {
        std::cout << "Success\n";
    } else {
        std::cout << "Failure\n";
        return 1;
    }

    /* Cleans up the OpenSSL context. */
    ECDSA_SIG_free(sig);
    EC_KEY_free(key);
    EC_GROUP_free(group);

    /* Cleans up after our own allocations. */
    delete args;

    return 0;
}
