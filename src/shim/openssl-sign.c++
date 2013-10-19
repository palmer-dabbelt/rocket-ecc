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
    Signature *signature;
    BIGNUM *kinv;
    BIGNUM *rp;

    /* Here we simply parse the command-line arguments. */
    args = new Args(argc, argv);

    /* Generates a new elliptic curve given the name the
     * commandline. */
    group = EC_GROUP_new_by_curve_name(args->curve->openssl_name());

    /* Allocates a new key and sets it to some known values */
    key = EC_KEY_new_by_curve_name(args->curve->openssl_name());
    if (key == NULL) {
        std::cerr << "Unable to allocate key structure\n";
        return 2;
    }

    /* Set the key to something known so we keep getting the same
     * signature every time, allowing the test harness to actually
     * run. */
    {
        BN_CTX *ctx;
        EC_POINT *pubkey;
        const char *pubkey_str;

        pubkey = EC_POINT_new(group);
        pubkey_str = args->public_key->hex.c_str();

        ctx = BN_CTX_new();
        pubkey = EC_POINT_hex2point(group, pubkey_str, pubkey, ctx);
        EC_KEY_set_public_key(key, pubkey);
        BN_CTX_free(ctx);
    }

    {
        BIGNUM *privkey;
        const char *privkey_str;
        
        privkey_str = args->private_key->hex.c_str();
        privkey = NULL;
        BN_hex2bn(&privkey, privkey_str);
        EC_KEY_set_private_key(key, privkey);
    }

    /* There are a few parameters used for ECDSA signatures.  It's
     * insecure to keep these constant, but it's actually better this
     * way because we get predictable signatures. */
    kinv = NULL;
    BN_hex2bn(&kinv, args->kinv->hex.c_str());
    if (kinv == NULL) {
        std::cerr << "Unable to parse kinv\n";
        return 2;
    }

    rp = NULL;
    BN_hex2bn(&rp, args->rp->hex.c_str());
    if (rp == NULL) {
        std::cerr << "Unable to parse rp\n";
        return 2;
    }

    /* Here's where we actually do the signature. */
    //ECDSA_sign_setup(key, NULL, &kinv, &rp);
    sig = ECDSA_do_sign_ex(args->digest->bytes(),
                           args->digest->byte_length(),
                           kinv, rp, key);
    if (sig == NULL) {
        std::cerr << "Unable to sign digest\n";
        return 2;
    }

    /* Verify the signature and fail if we don't get a proper
     * verification. */
    {
        int verified;

        verified = ECDSA_do_verify(args->digest->bytes(),
                                   args->digest->byte_length(),
                                   sig, key);

        if (verified != 1) {
            std::cerr << "Unable to verify signature\n";
            return 2;
        }
    }

    /* Finally convert the signature into a more standardized
     * format. */
    {
        signature = new Signature(BN_bn2hex(sig->r),
                                  BN_bn2hex(sig->s),
                                  i2d_ECDSA_SIG(sig, NULL));
    }

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
