#ifndef MCUS_CORTEXM0_COMMON_DRIVERS_NVIC_H
#define MCUS_CORTEXM0_COMMON_DRIVERS_NVIC_H


#include "common_peripherals.h"
#include "common_memmap.h"

#include "cpu.h" // defines HAS_SYSTICK if the MCU has SysTick timer

/**
 * macros to enable and disable all maskable interrupts
 */
#define enable_interrupts()   __asm__ ("CPSIE I")
#define disable_interrupts()  __asm__ ("CPSID I")

/**
 * Although on Cortex M0 unnecessary, it is architecturally correct to insert this instruction
 * after `enable_interrupts()` to ensure that any pending interrupts are executed prior to any
 * other thread instruction.
 * See http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dai0321a/BIHBFEIB.html
 */
#define instruction_sync_barrier()  __asm__ ("ISB")

/**
 * Enables the given interrupt (if applicable).
 *
 * This function will cause kernel panic if the interrupt number is invalid or if the state of this
 * interrupt cannot be controlled.
 *
 * Note: to enable SysTick system interrupt use the `systick_config` function from systick.h,
 * because enabling the SysTick interrupt without proper configuration is not a good idea.
 *
 * \param interrupt: Must be a hardware IRQ, cannot be one of system interrupts
 */
void enable_interrupt(const int interrupt);

/**
 * Disables the given interrupt (if applicable).
 *
 * This function will cause kernel panic if the interrupt number is invalid, if the interrupt cannot
 * be disabled or disabling the SysTick interrupt is attempted on systems lacking SysTick.
 *
 * \param interrupt: Must be hardware IRQ (or INT_SYSTICK on systems with SysTick), cannot be
 *                   one of the other system interrupts.
 */
void disable_interrupt(const int interrupt);

/**
 * Checks whether interrupt is enabled.
 *
 * This function will cause kernel panic if interrupt number is invalid.
 *
 * \param interrupt: could be any system interrupt, exception or hardware IRQ except INT_RESET or
 *                   on systems lacking SysTick except INT_SYSTICK.
 * \return true if interrupt is enabled, false otherwise
 */
bool is_interrupt_enabled(const int interrupt);

/**
 * Checks whether interrupt is pending.
 *
 * This function will cause kernel panic if interrupt number is invalid, if reading pending
 * state of INT_RESET, INT_SVCALL (since SVCall is synchronous) is attempted, or reading pending
 * state of INT_SYSTICK on systems lacking SysTick is attempted.
 *
 * \param interrupt: could be any system interrupt, exception or IRQ except INT_RESET and
 *                   INT_SVCALL, and on systems lacking SysTick except INT_SYSTICK.
 * \return true if interrupt is pending, false otherwise
 */
bool is_interrupt_pending(const int interrupt);

/**
 * Sets or clears pending state of interrupt.
 *
 * This function will cause kernel panic if interrupt number is invalid, if manipulating
 * pending state of INT_RESET or INT_SVCALL is attempted, clearing pending state of INT_NMI is
 * attempted or if manipulating INT_SYSTICK pending state on systems lacking SysTick is attempted.
 *
 * \param pending:   whether to set or clear pending state
 * \param interrupt: of what interrupt. Could be any system interrupt, exception or IRQ except
 *                   `Reset` and `SVCall` (and if `pending` is false also except `NMI`).
 *                   On systems lacking SysTick also except `SysTick`.
 */
void set_interrupt_pending(const int interrupt, const bool pending);

/**
 * Sets priority of interrupt.
 *
 * This function will cause kernel panic if the interrupt number is invalid, if setting priority
 * of an interrupt with fixed priority is attempted or if setting priority of INT_SYSTICK on systems
 * lacking SysTick is attempted.
 *
 * \param priority:  Priority of the interrupt. How many (most significant) bits of this value are
                     actually used is implementation-dependent (determined by the priority
                     granularity of the NVIC). This parameter can, however, be any value of uint8_t.
 * \param interrupt: Any system interrupt, exception or IRQ with configurable priority.
 *                   Therefore this cannot be INT_RESET, INT_HARDFAULT or INT_NMI (or INT_SYSTICK
 *                   on systems lacking SysTick).
 * \return the value rounded to implementation-defined granularity.
 */
uint8_t set_interrupt_priority(const uint8_t priority, const int interrupt);

/**
 * Gets priority of interrupt.
 *
 * This function will cause kernel panic if the interrupt number is invalid or is INT_SYSTICK and
 * the platform lacks SysTick.
 *
 * \param interrupt: Any system interrupt, exception or IRQ including fixed priority ones (except
                     `SysTick` on systems lacking SysTick).
 * \return priority of the interrupt, the lower the value the higher the priority. 0 is the highest
 *         user-configurable priority. May return a negative number for fixed-priority
 *         interrupts, like INT_RESET (-3), INT_NMI (-2) and INT_HARDFAULT (-1).
 */
int16_t get_interrupt_priority(const int interrupt);

/**
 * Checks whether any interrupts are pending.
 *
 * \return true if some interrupts are pending, false otherwise
 */
bool are_interrupts_pending();

/**
 * Gets the number of presently executing interrupt.
 *
 * \return interrupt number of presently executing interrupt, or 0 if the processor is in
 *         thread mode (no interrupt is presently executing)
 */
int get_executing_interrupt();

/**
 * Gets the number of presently pending interrupt with highest priority.
 *
 * \return interrupt number of the highest-priority pending interrupt, or 0 if no interrupts are
 *         pending
 */
int get_highest_pending_interrupt();


#endif
