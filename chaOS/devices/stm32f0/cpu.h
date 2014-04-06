/* CPU-specific information (STM32F0) */

// all general-purpose registers, plus sp, lr, pc
#define REGISTERS_SET  {r0-r15}
#define NUM_REGISTERS  16

// see http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0204f/Cihfddaf.html
#define _ARM_BLX_SHIT
