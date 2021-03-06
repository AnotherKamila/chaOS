/* defines Cortex M0 system interrupt numbers */

#ifndef MCUS_CORTEXM0_COMMON_SYSTEM_INTERRUPTS_H
#define MCUS_CORTEXM0_COMMON_SYSTEM_INTERRUPTS_H


/*
 * Those interrupts are numbered according to their exception numbers, see
 * http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0497a/BABBGBEC.html
 */

#define INT_RESET      1   // system reset exception
#define INT_NMI        2   // non-maskable interrupt
#define INT_HARDFAULT  3   // hardfault exception
#define INT_SVCALL     11  // supervisor call (software interrupt) -- used for system calls
#define INT_PENDSV     14  // request for service (asynchronous => use for "scheduling" stuff)
#define INT_SYSTICK    15  // system tick (generated by the configurable systick timer)

#define _IRQ_OFFSET    16  // used internally by the interrupt controller driver
#define _EXN_MAX       47  // maximum Cortex M0 exception number (higher numbers are futile!)

/*
 * To get IRQ number from interrupt number use interrupt_number - _IRQ_OFFSET
 */


#endif
