#include "ModIntHarness.h"
#include "modint.h++"

#include <assert.h>

#ifndef INIT_CYCLE_COUNT
#define INIT_CYCLE_COUNT 2
#endif

#pragma GCC diagnostic ignored "-Wunused-parameter"

enum func_type {
    FUNC_TYPE_ADD = 0,
    FUNC_TYPE_SUB = 1,
    FUNC_TYPE_MUL = 2,
    FUNC_TYPE_INV = 3,
    FUNC_TYPE_DIV = 4
};


/* These are some accessor functions to map between C++ ModInts and
 * Chisel ModInts. */
static ModInt run_in_chisel(const ModInt &a,
                            const ModInt &b,
                            enum func_type ft)
    __attribute__((unused));

#if 0
ModInt operator*(const ModInt &a, const ModInt &b)
{
    return run_in_chisel(a, b, FUNC_TYPE_MUL);
}
#endif

#if 0
ModInt ModInt::inverse(void) const
{
    return run_in_chisel(*this, *this, FUNC_TYPE_INV);
}
#endif

/* Static Methods */
ModInt run_in_chisel(const ModInt &a,
                     const ModInt &b,
                     enum func_type ft)
{
    ModIntHarness_t dut;
    int i;

    assert(a.mod() == b.mod());

    dut.init(true);
    dut.ModIntHarness__io_run = false;

    for (i = 0; i < INIT_CYCLE_COUNT; i++) {
        dut.clock_lo(true);
        dut.clock_hi(true);
    }

    dut.ModIntHarness__io_run = true;
    a.mod().write_array((uint64_t *)&dut.ModIntHarness__io_mod.values);
    a.data().write_array((uint64_t *)&dut.ModIntHarness__io_ina.values);
    b.data().write_array((uint64_t *)&dut.ModIntHarness__io_inb.values);
    dut.ModIntHarness__io_func = ft;

    do {
        dut.clock_lo(false);
        dut.clock_hi(false);

        dut.ModIntHarness__io_run = false;

        if (i > 1000 * 1000) {
            fprintf(stderr, "ModInt tests ran past %d cycles, aborting\n", i);
            fprintf(stderr, "Function was %d\n", ft);
            abort();
        }

        i++;
    } while (dut.ModIntHarness__io_busy.to_ulong() == 1);

    for (int j = 0; j < INIT_CYCLE_COUNT; j++, i++) {
        dut.clock_hi(false);
        dut.clock_lo(false);
    }

    BigInt bi((uint64_t *)&dut.ModIntHarness__io_out.values,
              false,
              MODINT_TEST_BIT_LENGTH);

    return ModInt(bi, a.mod());
}
