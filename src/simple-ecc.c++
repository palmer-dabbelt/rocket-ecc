#include <openssl/ec.h>
#include <openssl/ecdsa.h>
#include <openssl/obj_mac.h>

#include <stddef.h>
#include <stdio.h>

#define PUBKEY_STR "046120DAC05C1A9E2B9BDFC71C0C1BEB96C90CCED6630DF1B67C2CDEC5B53CCFFD5330D14EF72FBA9E1881ED63F57ED7E41C9D9923A64C2CACCF586E6AD9B24C0F"

#define PRIVKEY_STR "987C61120BD51F5164B0563BD3959D28CE87D1AC8D88FDD3A037F07668C59FBC"

#define KINV_STR "DB705ED7F892BCCD3EBBC9B84B17698736B0B4E94634E56AD30C71F7ABE4EDD5"

#define RP_STR "89C640EBC004A9DD7D01502557CB33814CA902876C4C7866E18934B3907CA648"

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
