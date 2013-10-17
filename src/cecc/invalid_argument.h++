#ifndef INVALID_ARGUMENT_HXX
#define INVALID_ARGUMENT_HXX

#include <string>

class InvalidArgument
{
public:
    std::string reason;

public:
    InvalidArgument(std::string reason);
};

#endif
