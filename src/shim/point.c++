#include "point.h++"

#include <iostream>
#include <stack>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Point::Point(std::string hex, const Curve *c)
    : _x(hex, 8                  , c->bit_length(), c->q()),
      _y(hex, c->bit_length() + 8, c->bit_length(), c->q())
{
    this->_c = c;
    assert(hex.length() == ((size_t)c->bit_length() / 2) + 2);
}

Point::Point(const ModInt &x, const ModInt &y, const Curve *c)
    : _x(x),
      _y(y)
{
    this->_c = c;
}

const char *Point::hex_cstr(void) const
{
    char *out;
    int r;

    r = asprintf(&out, "04%s%s", this->x_hex().c_str(), this->y_hex().c_str());
    if (r <= 0)
        abort();

    return out;
}

Point operator+(const Point &P, const Point &Q)
{
    assert(P._c == Q._c);
    const Curve *c = P._c;

    ModInt Px = P.x();
    ModInt Py = P.y();
    ModInt Qx = Q.x();
    ModInt Qy = Q.y();

    fprintf(stderr, "Px: %s\n", Px.hex_cstr());
    fprintf(stderr, "Py: %s\n", Py.hex_cstr());
    fprintf(stderr, "Qx: %s\n", Qx.hex_cstr());
    fprintf(stderr, "Qy: %s\n", Qy.hex_cstr());

    fprintf(stderr, "Py - Qy: %s\n", (Py - Qy).hex_cstr());
    fprintf(stderr, "Px - Qx: %s\n", (Px - Qx).hex_cstr());

    ModInt h = (Py - Qy) / (Px - Qx);
    ModInt h2 = h * h;

    fprintf(stderr, "h: %s\n",  h.hex_cstr());
    fprintf(stderr, "h2: %s\n", h2.hex_cstr());

    ModInt Rx = h2 - c->a() - Px - Qx;
    ModInt Ry = (h * (Px - Rx) - Py);

    return Point(Rx, Ry, c);
}

#ifdef POINT_TEST_HARNESS
int main(int argc, char **argv)
{
    int i;
    std::stack<ModInt> is;
    std::stack<Point> ps;
    const Curve *c = Curve::lookup_curve(argv[1]);

    for (i = 2; i < argc; i++) {
        std::cerr << "argv[" << i << "] = " << argv[i] << "\n";

        if (strcmp(argv[i], "point") == 0) {
            ModInt y = is.top(); is.pop();
            ModInt x = is.top(); is.pop();
            ps.push(Point(x, y, c));
        } else if (strcmp(argv[i], "pointadd") == 0) {
            Point y = ps.top(); ps.pop();
            Point x = ps.top(); ps.pop();
            ps.push(x + y);
        } else {
            BigInt bi(argv[i], c->bit_length());
            is.push(ModInt(bi, c->q()));
            std::cerr << "read " << is.top().hex() << "\n";
        }

#if 0
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
        } else {
            stack.push(BigInt(argv[i], BIGINT_TEST_BIT_LENGTH));
            std::cerr << "read " << stack.top().hex() << "\n";
        }
#endif
    }

    std::cout << ps.top().x_hex() << " " << ps.top().y_hex() << "\n";
}
#endif
