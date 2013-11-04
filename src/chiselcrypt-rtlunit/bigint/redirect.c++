#include "BigIntHarness.h"
#include "bigint.h++"

#include <assert.h>

#ifndef INIT_CYCLE_COUNT
#define INIT_CYCLE_COUNT 20
#endif

#pragma GCC diagnostic ignored "-Wunused-parameter"

enum func_type {
    FUNC_TYPE_ADD = 0,
    FUNC_TYPE_SUB = 1,
    FUNC_TYPE_MUL = 2,
    FUNC_TYPE_MOD = 3
};

/* These are some accessor functions to map between BigInts and Chisel
 * UInts. */
static BigInt run_in_chisel(const BigInt &, const BigInt &, enum func_type);

/* Here we overload some BigInt functions that can be tested directly
 * with Chisel code, allowing us to actually test that our Chisel code
 * does what we want. */
BigInt operator+(const BigInt &a, const BigInt &b)
{
    return run_in_chisel(a, b, FUNC_TYPE_ADD);
}

BigInt operator-(const BigInt &a, const BigInt &b)
{
    return run_in_chisel(a, b, FUNC_TYPE_SUB);
}

BigInt operator*(const BigInt &a, const BigInt &b)
{
    return run_in_chisel(a, b, FUNC_TYPE_MUL);
}

/* FIXME: We can't actually do long mods in Chisel. */
#if 0
BigInt operator%(const BigInt &a, const BigInt &b)
{
    return run_in_chisel(a, b, FUNC_TYPE_MOD);
}
#endif

/* Static Methods */
BigInt run_in_chisel(const BigInt &a, const BigInt &b, enum func_type ft)
{
    BigIntHarness_t dut;
    int i;

    dut.init(true);
    dut.BigIntHarness__io_run = false;

    for (i = 0; i < INIT_CYCLE_COUNT; i++) {
        dut.clock_hi(true);
        dut.clock_lo(true);
    }

    dut.BigIntHarness__io_run = true;
    a.write_array((uint64_t *)&dut.BigIntHarness__io_ina.values);
    b.write_array((uint64_t *)&dut.BigIntHarness__io_inb.values);
    dut.BigIntHarness__io_inao = a.overflow();
    dut.BigIntHarness__io_inbo = b.overflow();
    dut.BigIntHarness__io_func = ft;

    do {
        dut.clock_hi(false);
        dut.clock_lo(false);

        dut.BigIntHarness__io_run = false;

        i++;
    } while (dut.BigIntHarness__io_busy.to_ulong() == 1);

    for (int j = 0; j < INIT_CYCLE_COUNT; j++, i++) {
        dut.clock_lo(false);
        dut.clock_hi(false);
    }

    return BigInt((uint64_t *)&dut.BigIntHarness__io_out.values,
                  dut.BigIntHarness__io_oflo.to_ulong(),
                  BIGINT_TEST_BIT_LENGTH);
}
