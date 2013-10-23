#ifndef PUBLIC_KEY_HXX
#define PUBILC_KEY_HXX

#include "point.h++"
#include "curve.h++"

#include <string>

class PublicKey: public Point
{
public:
    PublicKey(std::string hex, const Curve *c);
};

#endif
