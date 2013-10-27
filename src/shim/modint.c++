#include "modint.h++"

#include <stack>
#include <iostream>
#include <string.h>
#include <assert.h>

ModInt::ModInt(std::string hex, int bit_length, BigInt mod)
    : _data(BigInt(hex, bit_length) % mod),
      _mod(mod)
{
}

ModInt::ModInt(std::string hex, int offset, int bit_length, BigInt mod)
    : _data(BigInt(hex, offset, bit_length) % mod),
      _mod(mod)
{
}

ModInt::ModInt(BigInt data, BigInt mod)
    : _data(data % mod),
      _mod(mod)
{
}

ModInt operator+(const ModInt &a, const ModInt &b)
{
    if (a._mod != b._mod)
        throw "Mis-matched modulus";

    ModInt out(a._data + b._data, a._mod);

    if (out._data > out._mod)
        return ModInt(out._data - a._mod, a._mod);

    return out;
}

ModInt operator-(const ModInt &a, const ModInt &b)
{
    if (a._mod != b._mod)
        throw "Mis-matched modulus";

    return ModInt(a._mod - b._data, a._mod) + a;
}

ModInt operator*(const ModInt &a, const ModInt &b)
{
    if (a._mod != b._mod)
        throw "Mis-matched modulus";

    return ModInt((a._data * b._data) % a._mod, a._mod);
}

#ifdef MODINT_TEST_HARNESS
int main(int argc, char **argv)
{
    int i;
    std::stack<ModInt> stack;
    BigInt mod(argv[1], BIGINT_BIT_LENGTH);

    for (i = 2; i < argc; i++) {
        std::cerr << "argv[" << i << "] = " << argv[i] << "\n";

        if (strcmp(argv[i], "+") == 0) {
            ModInt a = stack.top(); stack.pop();
            ModInt b = stack.top(); stack.pop();
            std::cerr << "sum1 " << a.hex() << "\n";
            std::cerr << "sum2 " << b.hex() << "\n";
            stack.push(a + b);
        } else if (strcmp(argv[i], "-") == 0) {
            ModInt a = stack.top(); stack.pop();
            ModInt b = stack.top(); stack.pop();
            std::cerr << "diff1 " << a.hex() << "\n";
            std::cerr << "diff2 " << b.hex() << "\n";
            stack.push(a - b);
#if 0
        } else if (strcmp(argv[i], "x") == 0) {
            ModInt a = stack.top(); stack.pop();
            ModInt b = stack.top(); stack.pop();
            std::cerr << "prod1 " << a.hex() << "\n";
            std::cerr << "prod2 " << b.hex() << "\n";
            stack.push(a * b);
#endif
        } else {
            stack.push(ModInt(argv[i], BIGINT_BIT_LENGTH, mod));
            std::cerr << "read " << stack.top().hex() << "\n";
        }
    }

    std::cout << stack.top().hex() << "\n";
}
#endif
