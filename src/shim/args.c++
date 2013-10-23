#include "args.h++"
#include "curve.h++"

#include <iostream>
#include <string>
#include <string.h>

Args::Args(int argc, char **argv)
{
    int i;

    /* Set default values for everything. */
    this->curve = Curve::lookup_curve("p256k1");
    this->digest = NULL;

    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--curve") == 0) {
            i++;

            try {
                this->curve = Curve::lookup_curve(argv[i]);
            } catch(InvalidArgument e) {
                std::cerr << "Error parsing '--curve " << argv[i] << "':\n";
                std::cerr << "  " << e.reason << "\n";
            }
        } else if (strcmp(argv[i], "--pubkey") == 0) {
            i++;

            try {
                this->public_key = new PublicKey(argv[i], this->curve);
            } catch(InvalidArgument e) {
                std::cerr << "Error parsing '--pubkey " << argv[i] << "':\n";
                std::cerr << "  " << e.reason << "\n";
            }
        } else if (strcmp(argv[i], "--privkey") == 0) {
            i++;

            try {
                this->private_key = new PrivateKey(argv[i],
                                                   curve->bit_length());
            } catch(InvalidArgument e) {
                std::cerr << "Error parsing '--privkey " << argv[i] << "':\n";
                std::cerr << "  " << e.reason << "\n";
            }
        } else if (strcmp(argv[i], "--kinv") == 0) {
            i++;

            try {
                this->kinv = new BigInt(argv[i], curve->bit_length());
            } catch(InvalidArgument e) {
                std::cerr << "Error parsing '--kinv " << argv[i] << "':\n";
                std::cerr << "  " << e.reason << "\n";
            }
        } else if (strcmp(argv[i], "--rp") == 0) {
            i++;

            try {
                this->rp = new BigInt(argv[i], curve->bit_length());
            } catch(InvalidArgument e) {
                std::cerr << "Error parsing '--rp " << argv[i] << "':\n";
                std::cerr << "  " << e.reason << "\n";
            }
        } else if (strcmp(argv[i], "--digest") == 0) {
            i++;

            try {
                this->digest = new Digest(argv[i], curve->bit_length());
            } catch(InvalidArgument e) {
                std::cerr << "Error parsing '--digest " << argv[i] << "':\n";
                std::cerr << "  " << e.reason << "\n";
            }
        } else if (strcmp(argv[i], "--r") == 0) {
            i++;

            try {
                this->r = new BigInt(argv[i], curve->bit_length());
            } catch(InvalidArgument e) {
                std::cerr << "Error parsing '--r " << argv[i] << "':\n";
                std::cerr << "  " << e.reason << "\n";
            }
        } else if (strcmp(argv[i], "--s") == 0) {
            i++;

            try {
                this->s = new BigInt(argv[i], curve->bit_length());
            } catch(InvalidArgument e) {
                std::cerr << "Error parsing '--s " << argv[i] << "':\n";
                std::cerr << "  " << e.reason << "\n";
            }
        } else {
            std::cerr << "Unknown argument '" << argv[i] << "':\n";
        }
    }
}
