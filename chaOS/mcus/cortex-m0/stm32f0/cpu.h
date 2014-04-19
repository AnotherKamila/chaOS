/* CPU-specific information (STM32F0) */

#ifndef DEVICES_STM32F0_CPU_H
#define DEVICES_STM32F0_CPU_H


// all general-purpose registers, plus sp, lr, pc
#define REGISTERS_SET  {r0-r15}
#define NUM_REGISTERS  16

// see http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0204f/Cihfddaf.html
#define ARM_BLX_SHIT  1


#endif
