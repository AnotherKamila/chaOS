/* Implements Nested Vectored Interrupt Controller driver for Cortex-M0 processors */

#include "core.h"
#include "nvic.h"
#include "util/bit_manip.h"
#include "kernel/panic.h"

#include "system_interrupts.h"
#include "hw_interrupts.h"

#include "systick.h"

/*
 * For interrupt numbering convention read comments and links in system_interrupts.h
 */

// This is used throughout this to find out whether we are dealing with IRQ
#define IS_IRQ(x) ((x) >= _IRQ_OFFSET)

/*
 * TODO not all 32 IRQs must be imeplemented by the MCU, if they aren't bits relating to them are
 * reserved. Fix that.
 */

intern void check_range(const int interrupt) {
    /*
     * see http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0497a/BABBGBEC.html
     * for allowed interrupt numbers
     */
    if ((interrupt < 0                                      ) ||
        (interrupt > INT_HARDFAULT && interrupt < INT_SVCALL) || // 1st reserved range
        (interrupt > INT_SVCALL    && interrupt < INT_PENDSV) || // 2nd reserved range
        (interrupt > _EXN_MAX) ) chaos("interrupt number out of range");

    // This feature is optional, and if missing related bits in registers are reserved
    #ifndef HAS_SYSTICK
    if (interrupt == INT_SYSTICK) chaos("no SysTick on this system (used INT_SYSTICK)");
    #endif
}

void enable_interrupt(const int interrupt) {
    if (IS_IRQ(interrupt)) {
        // We are dealing with an IRQ, not with system interrupt, use NVIC register
        // Bits in this registers correspond with IRQ numbers.
        bit_on(NVIC->ISER, interrupt - _IRQ_OFFSET);
    } else chaos("called enable_interrupt on system interrupt");
}

void disable_interrupt(const int interrupt) {
    check_range(interrupt);
    if (IS_IRQ(interrupt)) {
        // NVIC interrupts are disabled by writing 1 to ICER (Interrupt Clear Enable Register),
        // not by writing 0 to ISER
        bit_on(NVIC->ICER, interrupt - _IRQ_OFFSET);
    } else if (interrupt == INT_SYSTICK) {
        /*
         * Disabling systick interrupt is done by clearing TICKINT bit in the SysTick Control
         * and Status register. Hovewer we cannot do read-modify-write as reading SCR may clear
         * COUNTFLAG bit. SysTick driver is holding local copy of this register and will do this
         * for us.
         */
         systick_disable_interrupt();
    } else chaos("called disable_interupt on system interrupt");
}

bool is_interrupt_enabled(const int interrupt) {
    check_range(interrupt);
    if (IS_IRQ(interrupt)) {
        return NVIC->ISER & (1 << (interrupt - _IRQ_OFFSET));
    } else if (interrupt == INT_SYSTICK) {
        // Again, we cannot read SysTick SCR, let's ask SysTick driver instead
        return systick_is_interrupt_enabled();
    } else {
        // Someone is asking whether a system interrupt is enabled, and they always are
        return true;
    }
}

bool is_interrupt_pending(const int interrupt) {
    check_range(interrupt);
    if (IS_IRQ(interrupt)) {
        // For IRQ we must use NVIC registers
        return NVIC->ISPR & (1 << (interrupt - _IRQ_OFFSET));
    } else {
        // Some other system interrupts pending flags are in SCB registers
        switch (interrupt) {
            case INT_NMI:
                return SCB->ICSR & (1 << ICSR_NMIPENDSET);
            case INT_PENDSV:
                return SCB->ICSR & (1 << ICSR_PENDSVSET);
            case INT_SYSTICK:
                return SCB->ICSR & (1 << ICSR_PENDSTSET);
            default:
                chaos("given interrupt cannot be pending");
        }
    }
}

void set_interrupt_pending(const bool pending, const int interrupt) {
    check_range(interrupt);
    if (IS_IRQ(interrupt)) {
        if (pending) {
            /*
             * There is no need to do read-modify-write, as writing 0 to this register has
             * no effect.
             */
            NVIC->ISPR = (1 << (interrupt - _IRQ_OFFSET));
        } else {
            // Interrupt pending state is cleared by writing 1 to ICPR, not by writing 0 to ISPR
            NVIC->ICPR = (1 << (interrupt - _IRQ_OFFSET));
        }
    } else {
        switch (interrupt) {
            case INT_NMI:
                if (pending) SCB->ICSR |= (1 << ICSR_NMIPENDSET);
                else chaos("trying to clear pending state of NMI");
                break;
            case INT_SYSTICK:
                if (pending) SCB->ICSR |= (1 << ICSR_PENDSTSET);
                else SCB->ICSR |= (1 << ICSR_PENDSTCLR);
                break;
            case INT_PENDSV:
                if (pending) SCB->ICSR |= (1 << ICSR_PENDSVSET);
                else SCB->ICSR |= (1 << ICSR_PENDSVCLR);
                break;
        }
    }
}

uint8_t set_interrupt_priority(const uint8_t priority, const int interrupt) {
    check_range(interrupt);
    if (IS_IRQ(interrupt)) {
        unsigned int irq = interrupt - _IRQ_OFFSET;
        // This section must be atomic
        disable_interrupts();
        // There are 8 IPR registers, each holds 4 8-bit priority values for a given irq
        // Reset the original priority value
        NVIC->IPR[DIV4(irq)] &= ~(0xFF << (MOD4(irq) * 8));
        NVIC->IPR[DIV4(irq)] |= (priority << (MOD4(irq) * 8));
        enable_interrupts();
        /*
         * Processor may ignore writes to some LSB bits of this value to ensure
         * implementation-dependent value granularity. So let's return the real value we've
         * just set
         */
        return (NVIC->IPR[DIV4(irq)] >> (MOD4(irq) * 8)) & 0xFF;
    } else {
        uint8_t valshift = 0;
        uint8_t regnum = 0;
        switch (interrupt) {
            case INT_SVCALL:
                // SVCall priority bits are [31:24] in SHPR2 (SHPR[0]).
                valshift = 24;
                regnum = 0;
                break;
            case INT_SYSTICK:
                // SysTick priority bits are [31:24] in SHPR3 (SHPR[1]).
                valshift = 24;
                regnum = 1;
                break;
            case INT_PENDSV:
                // PendSV priority bits are [23:16] in SHPR3 (SHPR[1]).
                valshift = 16;
                regnum = 1;
                break;
            default:
                chaos("trying to set priority of a fixed-priority interrupt");
        }
        // If the interrupt num is invalid kernel is panic-ing, and this won't execute.
        disable_interrupts();
        SCB->SHPR[regnum] &= ~(0xFF << valshift);
        SCB->SHPR[regnum] |= ~(priority << valshift);
        enable_interrupts();
        return (SCB->SHPR[regnum] >> valshift) & 0xFF;
    }
}

int16_t get_interrupt_priority(const int interrupt) {
    check_range(interrupt);
    // See `set_interrupt_priority` for registers-related explanatory comments
    if (IS_IRQ(interrupt)) {
        unsigned int irq = interrupt - _IRQ_OFFSET;
        return (NVIC->IPR[DIV4(irq)] >> (MOD4(irq) * 8)) & 0xFF;
    } else {
        switch (interrupt) {
            case INT_SVCALL:
                return (SCB->SHPR[0] >> 24) & 0xFF;
            case INT_SYSTICK:
                return (SCB->SHPR[1] >> 24) & 0xFF;
            case INT_PENDSV:
                return (SCB->SHPR[1] >> 16) & 0xFF;
            /*
             * Those are fixed-priority interrupts, see
             * http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0497a/BABBGBEC.html
             */
            case INT_RESET:
                return -3;
            case INT_NMI:
                return -2;
            case INT_HARDFAULT:
                return -1;
            default:
                chaos("get priority of invalid system interrupt");
        }
    }
}

bool are_interrupts_pending() {
    // ICSR_ISRPENDING is indicating whether any hardware interrupt (IRQ) is pending
    return SCB->ICSR & ((1 << ICSR_ISRPENDING) |
                        (1 << ICSR_NMIPENDSET) |
                        (1 << ICSR_PENDSVSET)  |
                        (1 << ICSR_PENDSTSET));
}

int get_executing_interrupt() {
    // Number of presently executing interrupt is in ICSR (bits [5:0])
    return SCB->ICSR & 0x1F;
}

int get_highest_pending_interrupt() {
    // Number of pending interrupt with highest priority is in ICSR (bits [17:12])
    return (SCB->ICSR >> 12) & 0x1F;
}
