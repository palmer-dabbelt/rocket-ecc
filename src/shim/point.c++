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
    std::string x_str, y_str;

    x_str = this->x_hex();
    y_str = this->y_hex();

    out = (char *)malloc(strlen(x_str.c_str()) + strlen(y_str.c_str()) + 3);
    sprintf(out, "04%s%s", x_str.c_str(), y_str.c_str());

    return out;
}

Point operator+(const Point &P, const Point &Q) __attribute__((weak));
Point operator+(const Point &P, const Point &Q)
{
    if (P == Q)
        return point_dub(P);
    else
        return point_add(P, Q);
}

Point point_add(const Point &P, const Point &Q)
{
    assert(P._c == Q._c);
    const Curve *c = P._c;

    ModInt Px = P.x();
    ModInt Py = P.y();
    ModInt Qx = Q.x();
    ModInt Qy = Q.y();

    ModInt h = (Py - Qy) / (Px - Qx);
    ModInt h2 = h * h;

    ModInt Rx = h2 - Px - Qx;
    ModInt Ry = (h * (Px - Rx) - Py);

    return Point(Rx, Ry, c);
}

Point point_dub(const Point &P)
{
    const Curve *c = P._c;

    ModInt Px = P.x();
    ModInt Py = P.y();

    ModInt h = (3 * Px * Px + c->a()) / (2 * Py);
    ModInt h2 = h * h;

    ModInt Rx = h2 - Px - Px;
    ModInt Ry = (h * (Px - Rx) - Py);

    return Point(Rx, Ry, c);
}

Point operator*(const ModInt &d_in, const Point &P) __attribute__((weak));
Point operator*(const ModInt &d_in, const Point &P)
{
    Point R = Point(P._c->field(0), P._c->field(0), P._c);
    Point Q = P;
    ModInt d(d_in);
    bool set = false;

    for (int i = 0; i < d.bit_length(); i++) {
        if (d.is_odd()) {
            if (set)
                R = R + Q;
            else
                R = Q;

            set = true;
        }

        d = d >> 1;
        Q = Q + Q;
    }

    return R;
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
        } else if (strcmp(argv[i], "pointdub") == 0) {
            Point x = ps.top(); ps.pop();
            ps.push(x + x);
        } else if (strcmp(argv[i], "pointmul") == 0) {
            ModInt d = is.top(); is.pop();
            Point  P = ps.top(); ps.pop();
            ps.push(d * P);
        } else {
            BigInt bi(argv[i], c->bit_length());
            is.push(c->field(bi));
            std::cerr << "read " << is.top().hex() << "\n";
        }
    }

    for (i = 0; i < TEST_NEWLINE_COUNT; i++)
        std::cout << "\n";

    std::cout << ps.top().x_hex() << " " << ps.top().y_hex() << "\n";
}
#endif
