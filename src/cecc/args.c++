#include "args.h++"
#include "curve.h++"

#include <iostream>
#include <string>
#include <string.h>

#ifdef HAVE_OPENSSL
#include <openssl/obj_mac.h>
#endif

Args::Args(int argc, char **argv)
{
    int i;

    /* Set default values for everything. */
    this->curve = NULL;
    this->digest = NULL;

    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--curve") == 0) {
            i++;

            try {
                this->curve = new Curve(argv[i]);
            } catch(InvalidArgument e) {
                std::cerr << "Error parsing '--curve " << argv[i] << "':\n";
                std::cerr << "  " << e.reason << "\n";
            }
        } else if (strcmp(argv[i], "--pubkey") == 0) {
            i++;
        } else if (strcmp(argv[i], "--privkey") == 0) {
            i++;
        } else if (strcmp(argv[i], "--digest") == 0) {
            i++;

            try {
                this->digest = new Digest(argv[i], curve->size());
            } catch(InvalidArgument e) {
                std::cerr << "Error parsing '--digest " << argv[i] << "':\n";
                std::cerr << "  " << e.reason << "\n";
            }
        } else {
            std::cerr << "Unknown argument '" << argv[i] << "':\n";
        }
    }

    this->curve = new Curve();
}

#ifdef HAVE_OPENSSL
int Curve::openssl_name(void) const
{
    switch (this->type) {
    case TYPE_P_256_K_1:
        return NID_secp256k1;
    case TYPE_P_521_R_1:
        return NID_secp521r1;
    }

    /* This should never get here, but I guess the C++ compiler
     * doesn't detect that?  It's odd, because I belive C will... */
    return -1;
}
#endif
