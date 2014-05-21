#ifndef MCUS_CORTEXM0M4_COMMON_DRIVERS_SYSTICK_H
#define MCUS_CORTEXM0M4_COMMON_DRIVERS_SYSTICK_H

#include "common_peripherals.h"
#include "common_memmap.h"

#define SYSTICK_SUCCESS             0
#define SYSTICK_FEATURE_MISSING     1
#define SYSTICK_CALIB_UNKNOWN       2
#define SYSTICK_VAL_OUT_OF_RANGE    3

enum SysTick_clocksrc {
    SYSTICK_CLOCK_EXTERNAL  = 0,
    SYSTICK_CLOCK_PROCESSOR = 1,
};

#define SYSTICK_FLAG_ENABLED        1
#define SYSTICK_FLAG_DISABLED       0
#define SYSTICK_FLAG_NOREFC         2
#define SYSTICK_FLAG_NOEXACT        4
#define SYSTICK_FLAG_WASZERO        8

/**
 * Configures the SysTick timer. This also resets and disables the timer. This function MUST
 * be called before first call to `systick_enable()`.
 * \param clock is ignored if given CPU does not provide external reference clock
 */
int systick_config(const enum SysTick_clocksrc clock, const bool do_interrupt);

/**
 * Disables the SysTick interrupt
 */
void systick_disable_interrupt();

/**
 * Checks if the SysTick interrupt is enabled
 */
bool systick_is_interrupt_enabled();

/**
 * Enables the SysTick timer.
 *
 * After SysTick timer is enabled it starts counting down from current value.
 */
int systick_enable();

/**
 * Disables the SysTick timer.
 *
 * After disabled the timer stops counting, however its value is preserved.
 */
int systick_disable();

/**
 * Returns systick status flags.
 *
 * Return value may contain following flags:
 * SYSTICK_FLAG_DISABLED if SysTick is disabled or peripheral is missing
 * SYSTICK_FLAG_ENABLED if SysTick peripheral is present and enabled
 * SYSTICK_FLAG_NOREFC if no external reference clock is provided
 * SYSTICK_FLAG_NOEXACT if exact 10ms calibration value is not known
 * SYSTICK_FLAG_WASZERO if SysTick has reached zero since last check
 */
uint32_t systick_get_status();

/**
 * Reads the current SysTick timer value
 */
int systick_read(uint32_t * const value);

/**
 * Sets the current SysTick timer value
 */
int systick_write(const uint32_t value);

/**
 * Sets the SysTick timer reload value
 */
int systick_set_top(const uint32_t value);

/**
 * Gets the current SysTick timer reload value
 */
int systick_get_top(uint32_t * const value);

/**
 * Gets the exact SysTick 10ms calibration value or 0 if the value is not known.
 *
 * \return SYSTICK_CALIB_UNKNOWN if exact calibration value is not known.
 */
int systick_get_calibration(uint32_t * const value);

#endif
