#include "public_key.h++"

PublicKey::PublicKey(std::string hex, const Curve *c)
    : Point(hex, c)
{
}
