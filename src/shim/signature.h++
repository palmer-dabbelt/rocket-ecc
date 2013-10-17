#ifndef SIGNATURE_HXX
#define SIGNATURE_HXX

#include <string>

class Signature
{
private:
    int size;
    std::string r_hex;
    std::string s_hex;

public:
    /* Parses a signature from a pair of hex values. */
    Signature(std::string r_hex, std::string s_hex, int size);

    /* Obtains the two parameters. */
    std::string r(void) const;
    std::string s(void) const;
};

#endif
