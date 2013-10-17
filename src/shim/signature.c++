#include "signature.h++"

Signature::Signature(std::string r_hex, std::string s_hex, int size)
{
    this->size = size;
    this->r_hex = r_hex;
    this->s_hex = s_hex;
}

std::string Signature::r(void) const
{
    return this->r_hex;
}

std::string Signature::s(void) const
{
    return this->s_hex;
}
