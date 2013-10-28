#include "bigint.h++"
#include <assert.h>
#include <iostream>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Converts a hex character to an integer value. */
static int hex2int(unsigned char c);

BigInt::BigInt(std::string hex, int bit_length)
    : _bit_length(bit_length),
      _overflow(false)
{
    const char *str;

    str = hex.c_str();

    assert(this->bit_length() == 256);
    sscanf(str, "%016lx%016lx%016lx%016lx",
           this->_data + 0,
           this->_data + 1,
           this->_data + 2,
           this->_data + 3);
}

BigInt::BigInt(std::string hex, int offset, int bit_length)
    : _bit_length(bit_length),
      _overflow(false)
{
    const char *str;

    str = hex.c_str() + (offset / 4);

    assert(this->bit_length() == 256);
    sscanf(str, "%016lx%016lx%016lx%016lx",
           this->_data + 0,
           this->_data + 1,
           this->_data + 2,
           this->_data + 3);
}

BigInt::BigInt(const BigInt &other)
    : _bit_length(other._bit_length),
      _overflow(other._overflow)
{
    assert(this->bit_length() == other.bit_length());

    for (int i = 0; i < this->word_length(); i++)
        this->_data[i] = other._data[i];
}

BigInt::BigInt(int value, int bit_length)
    : _bit_length(bit_length),
      _overflow(false)
{
    for (int i = 0; i < this->word_length(); i++)
        this->_data[i] = 0;

    /* FIXME: GCC with optimizations complains when this isn't here.
     * I have no idea why.  The Internet suggests the warning
     * (-Werror=array-bounds) has lots of false positives, so I think
     * it's probably best to just work around. */
    assert(this->word_length() > 0);
    if (this->word_length() <= 0)
        abort();

    this->_data[this->word_length() - 1] = value;
}

std::string BigInt::hex(void) const
{
    char buf[1024];

    assert(this->bit_length() == 256);
    snprintf(buf, 1024, "%016lX%016lX%016lX%016lX",
             this->_data[0],
             this->_data[1],
             this->_data[2],
             this->_data[3]);

    return buf;
}

const char *BigInt::hex_cstr(void) const
{
    return strdup(this->hex().c_str());
}

const unsigned char *BigInt::byte_str(void) const
{
    const char *hex;
    unsigned char *bytes, *bytes_out;

    hex = this->hex_cstr();
    bytes = (unsigned char *)malloc((size_t)this->byte_length());
    bytes_out = bytes;

    for (int i = 0; i < this->byte_length(); i++) {
        unsigned int val;

        val = hex2int(*hex);
        val <<= 4;
        hex++;

        val += hex2int(*hex);
        hex++;

        *bytes = val;
        bytes++;
    }

    return bytes_out;
}

BigInt BigInt::extend(int new_bit_length) const
{
    BigInt out(0, new_bit_length);
    assert(new_bit_length >= this->bit_length());

    int offset = out.word_length() - this->word_length();
    for (int i = 0; i < this->word_length(); i++)
        out._data[i + offset] = this->_data[i];

    return out;
}

BigInt BigInt::trunc(int new_bit_length) const
{
    BigInt out(0, new_bit_length);
    assert(new_bit_length <= this->bit_length());

    int offset = this->word_length() - out.word_length();
    for (int i = 0; i < this->word_length(); i++)
        out._data[i] = this->_data[i + offset];

    return out;
}

BigInt operator+(const BigInt &a, const BigInt &b)
{
    assert(sizeof(a._data[0]) == 8);
    assert(a.bit_length() == b.bit_length());

    bigint_double_datum_t sum = 0;
    BigInt out(0, a.bit_length());
    for (int i = a.word_length()-1; i >= 0; i--) {
        sum += a._data[i];
        sum += b._data[i];
        out._data[i] = sum;
        sum >>= sizeof(sum) * 4;
    }

    out._overflow = (sum > 0) || a._overflow || b._overflow;

    return out;
}

BigInt operator-(const BigInt &a, const BigInt &b)
{
    assert(a.bit_length() == b.bit_length());

    BigInt out(a + (~b) + BigInt(1, a.bit_length()));

    if (a >= b)
        out._overflow = false;
    else
        out._overflow = true;

    return out;
}

BigInt operator*(const BigInt &a, const BigInt &b)
{
    assert(sizeof(a._data[0]) == 8);
    assert(a.bit_length() == b.bit_length());

    BigInt out(0, a.bit_length());
    bigint_double_datum_t  sum = 0;
    for (int p = a.word_length()-1; p >= 0; p--) {
        int count, i ,j;

        count = a.word_length() - p;
        i = a.word_length() - count;
        j = a.word_length() - 1;
        while (count > 0) {
            sum += (bigint_double_datum_t)(a._data[i])
                   * (bigint_double_datum_t)(b._data[j]);
            i++;
            j--;
            count--;
        }

        out._data[p] = sum;
        sum >>= sizeof(sum) * 4;
    }

    out._overflow = (sum > 0) || a._overflow || b._overflow;

    return out;
}

BigInt operator%(const BigInt &x, const BigInt &m)
{
    assert(m != 0);
    assert(x.bit_length() == m.bit_length());

    /* These two are special cases: the ModInt initialization code
     * calls this operator a whole bunch of times and I don't want to
     * bust out a whole shift/mod thing if I don't have to.  Usually
     * ModInt calls it with one of these two enabled, so this makes it
     * easier. */
#ifndef SKIP_SHORT_MOD
    if (x < m)
        return x;
    if (x - m < m)
        return x - m;

    assert(x > m);
#endif

    BigInt rem(x);
    BigInt acc(0, x.bit_length());

    for (int i = x.bit_length()-1; i >= 0; i--) {
        BigInt tri = m << i;

        acc = acc + acc;
        if (rem > tri) {
            rem = rem - tri;
            acc = acc + m;
        }
        
    }

    if (rem >= m)
        return rem - m;

    return rem;
}

BigInt BigInt::operator~(void) const
{
    BigInt out(0, this->bit_length());

    assert (this->bit_length() == out.bit_length());
    for (int i = 0; i < this->word_length(); i++)
        out._data[i] = ~this->_data[i];

    return out;
}

BigInt BigInt::operator<<(int i) const
{
    BigInt out(*this);

    for (i = i; i > 0; i--)
        out = out + out;

    return out;
}

BigInt BigInt::operator>>(int i) const
{
    BigInt out(*this);

    for (int j = 1; j < this->word_length(); j++) {
        bigint_double_datum_t d;

        d = this->_data[j-1];
        d <<= (sizeof(d) * 4);
        d += this->_data[j];

        d >>= i;

        out._data[j] = d;
    }

    out._data[0] = this->_data[0] >> i;

    return out;
}

bool operator==(const BigInt &a, const BigInt &b)
{
    assert(a.bit_length() == b.bit_length());

    for (int i = 0; i < a.word_length(); i++)
        if (a._data[i] != b._data[i])
            return false;

    return true;
}

bool operator>(const BigInt &a, const BigInt &b)
{
    assert(a.bit_length() == b.bit_length());

    if (a._overflow && !b._overflow)
        return true;
    if (!a._overflow && b._overflow)
        return false;

    for (int i = 0; i < a.word_length(); i++) {
        if (a._data[i] > b._data[i])
            return true;
        if (a._data[i] < b._data[i])
            return false;
    }

    return false;
}

bool operator>=(const BigInt &a, const BigInt &b)
{
    assert(a.bit_length() == b.bit_length());

    if (a._overflow && !b._overflow)
        return true;
    if (!a._overflow && b._overflow)
        return false;

    for (int i = 0; i < a.word_length(); i++) {
        if (a._data[i] > b._data[i])
            return true;
        if (a._data[i] < b._data[i])
            return false;
    }

    return true;
}

int hex2int(unsigned char c)
{
    switch (c) {
    case '0': return 0;
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    case '8': return 8;
    case '9': return 9;
    case 'a': return 10;
    case 'b': return 11;
    case 'c': return 12;
    case 'd': return 13;
    case 'e': return 14;
    case 'f': return 15;
    case 'A': return 10;
    case 'B': return 11;
    case 'C': return 12;
    case 'D': return 13;
    case 'E': return 14;
    case 'F': return 15;
    }

    return -1;
}

#ifdef BIGINT_TEST_HARNESS
int main(int argc, char **argv)
{
    int i;
    std::stack<BigInt> stack;

    for (i = 1; i < argc; i++) {
        std::cerr << "argv[" << i << "] = " << argv[i] << "\n";

        if (strcmp(argv[i], "+") == 0) {
            BigInt a = stack.top(); stack.pop();
            BigInt b = stack.top(); stack.pop();
            std::cerr << "sum1 " << a.hex() << "\n";
            std::cerr << "sum2 " << b.hex() << "\n";
            stack.push(a + b);
        } else if (strcmp(argv[i], "-") == 0) {
            BigInt a = stack.top(); stack.pop();
            BigInt b = stack.top(); stack.pop();
            std::cerr << "diff1 " << a.hex() << "\n";
            std::cerr << "diff2 " << b.hex() << "\n";
            stack.push(a - b);
        } else if (strcmp(argv[i], "x") == 0) {
            BigInt a = stack.top(); stack.pop();
            BigInt b = stack.top(); stack.pop();
            std::cerr << "prod1 " << a.hex() << "\n";
            std::cerr << "prod2 " << b.hex() << "\n";
            stack.push(a * b);
        } else if (strcmp(argv[i], "%") == 0) {
            BigInt a = stack.top(); stack.pop();
            BigInt b = stack.top(); stack.pop();
            std::cerr << "mod1 " << a.hex() << "\n";
            std::cerr << "mod2 " << b.hex() << "\n";
            stack.push(a % b);
        } else {
            stack.push(BigInt(argv[i], BIGINT_TEST_BIT_LENGTH));
            std::cerr << "read " << stack.top().hex() << "\n";
        }
    }

    std::cout << stack.top().hex() << " " << stack.top().of_str() << "\n";
}
#endif
