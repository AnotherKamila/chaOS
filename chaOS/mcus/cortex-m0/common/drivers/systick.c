/* Implements SysTick timer for Cortex-M0 processors */

#include "systick.h"
#include "util/bit_manip.h"

//This header should define HAS_SYSTICK if CPU we are compiling for has it
#include "cpu.h"

/*
 * We must never read the CSR register (except for reading COUNTFLAG flag) because COUNTFLAG
 * is reset after every read. This is its local copy for read-modify-write
 */
static uint32_t csr_local;

int systick_config(const enum SysTick_clocksrc clock, const bool do_interrupt) {
    #ifndef HAS_SYSTICK
    return SYSTICK_FEATURE_MISSING;
    #else

    csr_local = 0;

    //Systick current and reload value are undefined at reset, this is the recommended init order:
    systick_disable(); //If by any chance it was enabled
    systick_set_top(0);
    systick_write(0);

    bit_moff(csr_local, (1 << CSR_CLKSOURCE) | (1 << CSR_TICKINT));
    bit_mon(csr_local, (clock << CSR_CLKSOURCE) | (do_interrupt << CSR_TICKINT));

    STK->CSR = csr_local;

    return SYSTICK_SUCCESS;
    #endif
}

void systick_disable_interrupt() {
    #ifdef HAS_SYSTICK
    bit_moff(csr_local, (1 << CSR_TICKINT));
    STK->CSR = csr_local;
    #endif
}

bool systick_is_interrupt_enabled() {
    #ifdef HAS_SYSTICK
    return csr_local & (1 << CSR_TICKINT);
    #else
    return false
    #endif
}

int systick_enable() {
    #ifndef HAS_SYSTICK
    return SYSTICK_FEATURE_MISSING;
    #else
    bit_mon(csr_local, (1 << CSR_ENABLE));
    STK->CSR = csr_local;
    return SYSTICK_SUCCESS;
    #endif
}

int systick_disable() {
    #ifndef HAS_SYSTICK
    return SYSTICK_FEATURE_MISSING;
    #else
    bit_moff(csr_local, (1 << CSR_ENABLE));
    STK->CSR = csr_local;
    return SYSTICK_SUCCESS;
    #endif
}

uint32_t systick_get_status() {
    #ifndef HAS_SYSTICK
    return SYSTICK_FLAG_DISABLED;
    #else
    uint32_t flags = 0;
    if (csr_local & (1 << CSR_ENABLE)) flags |= SYSTICK_FLAG_ENABLED;
    if (STK->CALIB & (1 << CALIB_NOREF)) flags |= SYSTICK_FLAG_NOREFC;
    if (STK->CALIB & (1 << CALIB_SKEW)) flags |= SYSTICK_FLAG_NOEXACT;
    // After this read completes the COUNTFLAG resets
    if (STK->CSR & (1 << CSR_COUNTFLAG)) flags |= SYSTICK_FLAG_WASZERO;
    return flags;
    #endif
}

int systick_read(uint32_t *value) {
    #ifndef HAS_SYSTICK
    return SYSTICK_FEATURE_MISSING;
    #else
    *value = STK->CVR;
    return SYSTICK_SUCCESS;
    #endif
}

int systick_write(uint32_t value) {
    #ifndef HAS_SYSTICK
    return SYSTICK_FEATURE_MISSING;
    #else
    if (value & 0xFF000000) {
        //Highest 8 bits are reserved and cannot be written to
        return SYSTICK_VAL_OUT_OF_RANGE;
    }
    STK->CVR = value;
    return SYSTICK_SUCCESS;
    #endif
}

int systick_set_top(uint32_t value) {
    #ifndef HAS_SYSTICK
    return SYSTICK_FEATURE_MISSING;
    #else
    if (value & 0xFF000000) {
        //Highest 8 bits are reserved and cannot be written to
        return SYSTICK_VAL_OUT_OF_RANGE;
    }
    STK->RVR = value;
    return SYSTICK_SUCCESS;
    #endif
}

int systick_get_top(uint32_t *value) {
    #ifndef HAS_SYSTICK
    return SYSTICK_FEATURE_MISSING;
    #else
    *value = STK->RVR;
    return SYSTICK_SUCCESS;
    #endif
}

int systick_get_calibration(uint32_t *value) {
    #ifndef HAS_SYSTICK
    return SYSTICK_FEATURE_MISSING;
    #else
    //Mask out reserved bits
    if (STK->CALIB & 0x00FFFFFF) {
        //Calibration value is not zero, therefore is known
        *value = STK->CALIB & 0x00FFFFFF;
        return SYSTICK_SUCCESS;
    } else {
        *value = 0;
        return SYSTICK_CALIB_UNKNOWN;
    }
    #endif
}
