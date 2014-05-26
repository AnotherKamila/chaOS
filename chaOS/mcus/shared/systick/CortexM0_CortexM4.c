/* Implements SysTick timer for Cortex-M0 and Cortex-M4 processors */

#include "systick.h"
#include "util/bit_manip.h"

//This header should define HAS_SYSTICK if CPU we are compiling for has it
#include "cpu.h"

#if !HAS_SYSTICK // no SysTick => provide only stub functions returning SYSTICK_FEATURE_MISSING

int systick_config(const enum SysTick_clocksrc clock __attribute__((unused)),
                   const bool do_interrupt __attribute__((unused))) {
    return SYSTICK_FEATURE_MISSING;
}

bool systick_is_interrupt_enabled() {
    return false; // if systick is missing its interrupt cannot be enabled
}

uint32_t systick_get_status() {
    return SYSTICK_FLAG_DISABLED; // If systick is missing it cannot be enabled
}

void systick_disable_interrupt() { }
int systick_enable() { return SYSTICK_FEATURE_MISSING; }
int systick_disable() { return SYSTICK_FEATURE_MISSING; }

int systick_read(uint32_t * const v __attribute__((unused))) { return SYSTICK_FEATURE_MISSING; }
int systick_write(const uint32_t v __attribute__((unused))) { return SYSTICK_FEATURE_MISSING; }
int systick_set_top(const uint32_t v __attribute__((unused))) { return SYSTICK_FEATURE_MISSING; }
int systick_get_top(uint32_t * const v __attribute__((unused))) { return SYSTICK_FEATURE_MISSING; }
int systick_get_calibration(uint32_t *const v __attribute__((unused))) {
    return SYSTICK_FEATURE_MISSING;
}

#else // SysTick is present => implement the driver

/*
 * We must never read the CSR register (except for reading COUNTFLAG flag) because COUNTFLAG
 * is reset after every read. This is its local copy for read-modify-write
 */
static uint32_t csr_local;

int systick_config(const enum SysTick_clocksrc clock, const bool do_interrupt) {
    csr_local = 0;

    // SysTick current and reload values are undefined at reset, this is the recommended init order:
    systick_disable(); // if by any chance it was enabled
    systick_set_top(0);
    systick_write(0);

    bits_off(csr_local, (1 << CSR_CLKSOURCE) | (1 << CSR_TICKINT));
    bits_on(csr_local, (clock << CSR_CLKSOURCE) | (((uint32_t)do_interrupt) << CSR_TICKINT));

    STK->CSR = csr_local;

    return SYSTICK_SUCCESS;
}

void systick_disable_interrupt() {
    bits_off(csr_local, (1 << CSR_TICKINT));
    STK->CSR = csr_local;
}

bool systick_is_interrupt_enabled() {
    return csr_local & (1 << CSR_TICKINT);
}

int systick_enable() {
    bits_on(csr_local, (1 << CSR_ENABLE));
    STK->CSR = csr_local;
    return SYSTICK_SUCCESS;
}

int systick_disable() {
    bits_off(csr_local, (1 << CSR_ENABLE));
    STK->CSR = csr_local;
    return SYSTICK_SUCCESS;
}

uint32_t systick_get_status() {
    uint32_t flags = 0;
    if (csr_local & (1 << CSR_ENABLE)) flags |= SYSTICK_FLAG_ENABLED;
    if (STK->CALIB & (1 << CALIB_NOREF)) flags |= SYSTICK_FLAG_NOREFC;
    if (STK->CALIB & (1 << CALIB_SKEW)) flags |= SYSTICK_FLAG_NOEXACT;
    // after this read completes, COUNTFLAG is reset
    if (STK->CSR & (1 << CSR_COUNTFLAG)) flags |= SYSTICK_FLAG_WASZERO;
    return flags;
}

int systick_read(uint32_t * const value) {
    *value = STK->CVR;
    return SYSTICK_SUCCESS;
}

int systick_write(const uint32_t value) {
    if (value & 0xFF000000) {
        // highest 8 bits are reserved and cannot be written to
        return SYSTICK_VAL_OUT_OF_RANGE;
    }
    STK->CVR = value;
    return SYSTICK_SUCCESS;
}

int systick_set_top(const uint32_t value) {
    if (value & 0xFF000000) {
        // highest 8 bits are reserved and cannot be written to
        return SYSTICK_VAL_OUT_OF_RANGE;
    }
    STK->RVR = value;
    return SYSTICK_SUCCESS;
}

int systick_get_top(uint32_t * const value) {
    *value = STK->RVR;
    return SYSTICK_SUCCESS;
}

int systick_get_calibration(uint32_t * const value) {
    // mask out reserved bits
    if (STK->CALIB & 0x00FFFFFF) {
        // calibration value is not zero, therefore is known
        *value = STK->CALIB & 0x00FFFFFF;
        return SYSTICK_SUCCESS;
    } else {
        *value = 0;
        return SYSTICK_CALIB_UNKNOWN;
    }
}

#endif
