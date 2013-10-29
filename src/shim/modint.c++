#include "modint.h++"

#include <stack>
#include <iostream>
#include <string.h>
#include <assert.h>
#include <stdio.h>

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
    assert(a._mod == b._mod);

    BigInt ade = a._data.extend2x();
    BigInt bde = b._data.extend2x();
    BigInt me  = a._mod.extend2x();

    return ModInt(trunc2x((ade * bde) % me), a._mod);
}

ModInt operator/(const ModInt &a, const ModInt &b)
{
    assert(a._mod == b._mod);
    assert(a.bit_length() == b.bit_length());
    return ModInt(a._data * b.inverse(), a._mod);
}

/* FIXME: This is horribly, terribly afwul.  I think that I have to
 * double the length of everything to avoid overflow, and there's that
 * afwul multiplication check in there as well. */
BigInt ModInt::inverse(void) const
{
    BigInt p = this->_mod.extend2x();
    int bit_length = this->bit_length();

    /* Here we compute the modular inverse of b, according to the NIST
     * mechanism. */
    BigInt u = this->_data.extend2x();
    BigInt v = p;

    BigInt x1 = BigInt(1, 2*bit_length);
    BigInt x2 = BigInt(0, 2*bit_length);

    while (u != 0) {
        /* I have no idea why these need to exist.  It seems like I
         * have one termination condition from the NIST algorithm (for
         * non-prime P), and another termination condition from a
         * different paper (for prime P).  Neither of them works in
         * both cases, so I just go and check... */
        {
            ModInt x1m(x1.trunc2x(), this->_mod);
            if ((u == 1) && (x1m * (*this) == 1))
                return x1.trunc2x();
        }

        {
            ModInt x2m(x2.trunc2x(), this->_mod);
            if ((v == 1) && (x2m * (*this) == 1))
                return x2.trunc2x();
        }

        while (u.is_even()) {
            u = u >> 1;

            if (x1.is_even())
                x1 = x1 >> 1;
            else
                x1 = add_shift_one(x1, p);
        }

        while (v.is_even()) {
            v = v >> 1;

            if (x2.is_even())
                x2 = x2 >> 1;
            else
                x2 = add_shift_one(x2, p);
        }

        if (u >= v) {
            u = ((u + p) - v) % p;
            x1 = ((x1 + p) - x2) % p;
        } else {
            v = ((v + p) - u) % p;
            x2 = ((x2 + p) - x1) % p;
        }
    }

    return trunc2x(x1 % p);
}

#ifdef MODINT_TEST_HARNESS
int main(int argc, char **argv)
{
    int i;
    std::stack<ModInt> stack;
    BigInt mod(argv[1], MODINT_TEST_BIT_LENGTH);

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
        } else if (strcmp(argv[i], "x") == 0) {
            ModInt a = stack.top(); stack.pop();
            ModInt b = stack.top(); stack.pop();
            std::cerr << "prod1 " << a.hex() << "\n";
            std::cerr << "prod2 " << b.hex() << "\n";
            stack.push(a * b);
        } else if (strcmp(argv[i], "/") == 0) {
            ModInt a = stack.top(); stack.pop();
            ModInt b = stack.top(); stack.pop();
            std::cerr << "div1 " << a.hex() << "\n";
            std::cerr << "div2 " << b.hex() << "\n";
            stack.push(a / b);
        } else if (strcmp(argv[i], "inv") == 0) {
            ModInt a = stack.top(); stack.pop();
            std::cerr << "inv1 " << a.hex() << "\n";

            ModInt inv(a.inverse(), mod);
            std::cerr << "inv " << inv.hex() << "\n";

            std::cerr << "invprod " << (inv * a).hex() << "\n";
            if ((inv * a) != 1)
                std::cerr << "Modular Inversion Failed\n";

            assert((inv * a) == 1);
            stack.push(inv);
        } else {
            stack.push(ModInt(argv[i], MODINT_TEST_BIT_LENGTH, mod));
            std::cerr << "read " << stack.top().hex() << "\n";
        }
    }

    std::cout << stack.top().hex() << "\n";
}
#endif
