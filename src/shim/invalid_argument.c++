#include "invalid_argument.h++"

#include <stdlib.h>
#include <string.h>

InvalidArgument::InvalidArgument(std::string reason)
{
    this->reason = reason;
}
