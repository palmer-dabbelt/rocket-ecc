#include "ModIntHarness.h"
#include "modint.h++"

#include <assert.h>

#ifndef INIT_CYCLE_COUNT
#define INIT_CYCLE_COUNT 10
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

ModInt operator+(const ModInt &a, const ModInt &b)
{
    return run_in_chisel(a, b, FUNC_TYPE_ADD);
}

ModInt operator-(const ModInt &a, const ModInt &b)
{
    return run_in_chisel(a, b, FUNC_TYPE_SUB);
}

#if 0
ModInt operator*(const ModInt &a, const ModInt &b)
{
    return run_in_chisel(a, b, FUNC_TYPE_MUL);
}
#endif

ModInt ModInt::inverse(void) const
{
    return run_in_chisel(*this, *this, FUNC_TYPE_INV);
}

/* Static Methods */
ModInt run_in_chisel(const ModInt &a,
                     const ModInt &b,
                     enum func_type ft)
{
    ModIntHarness_t dut;
    int i;
#ifdef PRINT_FILE
    FILE *f = fopen("/tmp/chisel.vcd", "w");
#endif

    assert(a.mod() == b.mod());

    dut.init(true);
    dut.ModIntHarness__io_run = false;

    for (i = 0; i < INIT_CYCLE_COUNT; i++) {
        dut.clock(true);
#ifdef PRINT_FILE
        dut.dump(f, i);
#endif
    }

    dut.ModIntHarness__io_run = true;
    a.mod().write_array((uint64_t *)&dut.ModIntHarness__io_mod.values);
    a.data().write_array((uint64_t *)&dut.ModIntHarness__io_ina.values);
    b.data().write_array((uint64_t *)&dut.ModIntHarness__io_inb.values);
    dut.ModIntHarness__io_func = ft;

    do {
        dut.clock(false);
#ifdef PRINT_FILE
        dut.dump(f, i);
#endif

        dut.ModIntHarness__io_run = false;

        if (i > 10000) {
            fprintf(stderr, "ModInt tests ran past %d cycles, aborting\n", i);
            fprintf(stderr, "Function was %d\n", ft);
            abort();
        }

        i++;
    } while (dut.ModIntHarness__io_busy.to_ulong() == 1);

    for (int j = 0; j < INIT_CYCLE_COUNT; j++, i++) {
        dut.clock(false);
#ifdef PRINT_FILE
        dut.dump(f, i);
#endif
    }

    BigInt bi((uint64_t *)&dut.ModIntHarness__io_out.values,
              false,
              MODINT_TEST_BIT_LENGTH);

    return ModInt(bi, a.mod());
}
