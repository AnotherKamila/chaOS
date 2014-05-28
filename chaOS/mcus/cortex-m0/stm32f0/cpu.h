/* CPU-specific information (STM32F0) */

#ifndef DEVICES_STM32F0_CPU_H
#define DEVICES_STM32F0_CPU_H


// all general-purpose registers, plus sp, lr, pc
#define REGISTERS_SET  {r0-r15}
#define NUM_REGISTERS  16

//SysTick feature is optional, STM32F0 MCUs do have it.
#define HAS_SYSTICK  1


#endif
