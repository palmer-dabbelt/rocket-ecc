#include "modint.h++"

ModInt::ModInt(std::string hex, int offset, int bit_length, BigInt mod)
    : _data(hex, offset, bit_length),
      _mod(mod)
{
}

ModInt::ModInt(BigInt data, BigInt mod)
    : _data(data),
      _mod(mod)
{
}

ModInt operator+(const ModInt &a, const ModInt &b)
{
    if (a._mod != b._mod)
        throw "Mis-matched modulus";

    ModInt out(a._data + b._data, a._mod);

    if (out._data > out._mod)
        return ModInt(a._data + b._data - a._mod, a._mod);

    return out;
}

ModInt operator-(const ModInt &a, const ModInt &b)
{
    if (a._mod != b._mod)
        throw "Mis-matched modulus";

    ModInt out(a._data - b._data, a._mod);

    if (out._data > out._mod)
        return ModInt(a._data - b._data + a._mod, a._mod);

    return out;
}

ModInt operator*(const ModInt &a, const ModInt &b)
{
    if (a._mod != b._mod)
        throw "Mis-matched modulus";

    ModInt out(BigInt::monty_mult(a._data, b._data, a._mod), a._mod);

    return out;
}
