#ifndef ARGS_HXX
#define ARGS_HXX

#include "curve.h++"
#include "digest.h++"

/* Parses the commandline argumens that are known to CECC. */
class Args
{
public:
    Curve *curve;
    Digest *digest;

public:
    Args(int argc, char **argv);
};

#endif
