#include "PointHarness.h"
#include "point.h++"

#include <assert.h>

#ifndef INIT_CYCLE_COUNT
#define INIT_CYCLE_COUNT 10
#endif

enum func_type {
    FUNC_TYPE_ADD = 0,
    FUNC_TYPE_MUL = 1
};

/* These are some accessor functions to map between C++ ModInts and
 * Chisel ModInts. */
static Point run_in_chisel(const Point &a,
                           const Point &b,
                           enum func_type ft)
    __attribute__((unused));

#if 0
Point operator+(const Point &a, const Point &b)
{
    return run_in_chisel(a, b, FUNC_TYPE_ADD);
}
#endif

/* Static Methods */
Point run_in_chisel(const Point &a,
                    const Point &b,
                    enum func_type ft)
{
    PointHarness_t dut;
    int i;
#ifdef PRINT_FILE
    FILE *f = fopen("/tmp/chisel.vcd", "w");
#endif

    assert(a.x().mod() == a.x().mod());
    assert(a.x().mod() == b.x().mod());
    assert(a.y().mod() == b.y().mod());
    assert(a.y().mod() == a.y().mod());

    dut.init(true);
    dut.PointHarness__io_run = false;

    for (i = 0; i < INIT_CYCLE_COUNT; i++) {
        dut.clock(true);
#ifdef PRINT_FILE
        dut.dump(f, i);
#endif
    }

    dut.PointHarness__io_run = true;
    a.x().mod().write_array((uint64_t *)&dut.PointHarness__io_mod.values);
    a.x().data().write_array((uint64_t *)&dut.PointHarness__io_inax.values);
    a.y().data().write_array((uint64_t *)&dut.PointHarness__io_inay.values);
    b.x().data().write_array((uint64_t *)&dut.PointHarness__io_inbx.values);
    b.y().data().write_array((uint64_t *)&dut.PointHarness__io_inby.values);
    dut.PointHarness__io_func = ft;

    do {
        dut.clock(false);
#ifdef PRINT_FILE
        dut.dump(f, i);
#endif

        dut.PointHarness__io_run = false;

        if (i > 10000) {
            fprintf(stderr, "ModInt tests ran past %d cycles, aborting\n", i);
            fprintf(stderr, "Function was %d\n", ft);
            abort();
        }

        i++;
    } while (dut.PointHarness__io_busy.to_ulong() == 1);

    for (int j = 0; j < INIT_CYCLE_COUNT; j++, i++) {
        dut.clock(false);
#ifdef PRINT_FILE
        dut.dump(f, i);
#endif
    }

    BigInt bix((uint64_t *)&dut.PointHarness__io_outx.values,
               false,
               POINT_TEST_BIT_LENGTH);

    BigInt biy((uint64_t *)&dut.PointHarness__io_outy.values,
               false,
               POINT_TEST_BIT_LENGTH);

    return Point(ModInt(bix, a.x().mod()), ModInt(biy, a.y().mod()), a.c());
}
