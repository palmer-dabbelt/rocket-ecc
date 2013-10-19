#include <openssl/ec.h>
#include <openssl/ecdsa.h>
#include <openssl/obj_mac.h>

#include <stddef.h>
#include <stdio.h>

#define PUBKEY_STR "04563A2A5F1C9D8B5BB8FBE691DDF768C63A80BB7FDE9432D4E29FE16C1549B4A790A9610D42A3613D8E67A7188205B281D08B950247EA40F9CF1DC13F4EDEEB50"

#define PRIVKEY_STR "1B150C158F2DB9662FA6B2644986E4CFF87F4A096211CF01A07E9E130A5EAD3D"

#define KINV_STR "675C325BDEB8F3DBB6B7105D07F92508F0DEB8DE6E72A6E289F753FB8D66FB30"

#define RP_STR "8F17358448DE9EFC040B0B9B8B23706256DEE87BEAB4692F766D8721A24270C8"

#define DIGEST_LEN 64
#define DIGEST_STR ((const unsigned char *)"6b5dfcd5031a5fd18d9298421dfcf2da5320bea8524b26d2ca1419777207f2ea")


int main(int argc __attribute__((unused)),
         char **argv __attribute__((unused)))
{
    EC_GROUP *group;
    EC_KEY *key;
    ECDSA_SIG *sig;
    BIGNUM *kinv;
    BIGNUM *rp;
    int out;

    group = EC_GROUP_new_by_curve_name(NID_secp256k1);
    if (group == NULL)
        abort();

    key = EC_KEY_new_by_curve_name(NID_secp256k1);
    if (key == NULL)
        abort();

    {
        BN_CTX *ctx;
        EC_POINT *pubkey;

        pubkey = EC_POINT_new(group);

        ctx = BN_CTX_new();
        pubkey = EC_POINT_hex2point(group, PUBKEY_STR, pubkey, ctx);

        if (EC_KEY_set_public_key(key, pubkey) != 1)
            abort();
    }

    {
        BIGNUM *privkey;
        
        privkey = NULL;
        BN_hex2bn(&privkey, PRIVKEY_STR);
        if (EC_KEY_set_private_key(key, privkey) != 1)
            abort();
    }
    
    if (!EC_KEY_check_key(key))
        abort();

    kinv = NULL;
    BN_hex2bn(&kinv, KINV_STR);
    if (kinv == NULL)
        abort();

    rp = NULL;
    BN_hex2bn(&rp, RP_STR);
    if (rp == NULL)
        abort();

#ifdef DO_SETUP
    {
        BN_CTX *ctx;

        ctx = BN_CTX_new();
        ECDSA_sign_setup(key, ctx, &kinv, &rp);
    }
#endif

    sig = ECDSA_do_sign_ex(DIGEST_STR, DIGEST_LEN, kinv, rp, key);
    if (sig == NULL)
        abort();

    {
        int v;

        v = ECDSA_do_verify(DIGEST_STR, DIGEST_LEN, sig, key);

        switch (v) {
        case 0:
            printf("Failure\n");
            out = 1;
            break;
        case 1:
            printf("Sucess\n");
            out = 0;
            break;
        case 2:
            printf("Error\n");
            out = 2;
            break;
        }
    }

    printf("R: hex %s\n", BN_bn2hex(sig->r));
    printf("S: hex %s\n", BN_bn2hex(sig->s));
    printf("KINV: hex %s\n", BN_bn2hex(kinv));
    printf("RP: hex %s\n", BN_bn2hex(rp));

    return out;
}
