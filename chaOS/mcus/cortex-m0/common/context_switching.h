#ifndef MCUS_CORTEXM0_COMMON_STACK_MANIP_H
#define MCUS_CORTEXM0_COMMON_STACK_MANIP_H


#include "core.h"

/** Returns the current PSP value. */
void *get_psp(void);

/** Loads the PSP with the given value. */
void set_psp(void* new_sp);

/**
 * creates initial frames for saved registers on the stack, and moves the stack pointer
 * appropriately
 */
void prepare_task_stack(void **sp, void *start, void at_end(void));

// see Figure 9 (Cortex-M0 stack frame layout) on page 26 of the Cortex-M0 programming manual
typedef struct {
    word r0;
    word r1;
    word r2;
    word r3;
    word r12;
    word lr;
    word pc;
    word psr;
} registers_frame_hw_t;

typedef struct {
    word r8;
    word r9;
    word r10;
    word r11;
    word r4;
    word r5;
    word r6;
    word r7;
} registers_frame_sw_t;

#define SAVE_CONTEXT()                                                                             \
    __asm__ volatile ("MRS r3, PSP\n\t" /* read the process stack pointer into r3 */               \
                      "SUB r3, r3, %[halfframe]\n\t" /* STM increments after, so move sp */        \
                      "STMIA r3!, {r4-r7}\n\t" /* store r4-r7 on the process stack, inc sp */      \
                      "SUB r3, r3, %[frame]\n\t" /* STM increments after, so move sp */            \
                      "MOV r4, r8\n\t"  /*                                                      */ \
                      "MOV r5, r9\n\t"  /* high registers cannot be stored to memory directly,  */ \
                      "MOV r6, r10\n\t" /* therefore I copy them to those that can...           */ \
                      "MOV r7, r11\n\t" /*                                                      */ \
                      "STMIA r3!, {r4-r7}\n\t" /* now we're actually storing r8-r11 ;) */          \
                      "SUB r3, r3, %[halfframe]\n\t" /* STM increments after, so move sp */        \
                      "MSR PSP, r3\n\t" /* update the real PSP */                                  \
                      :: [frame] "I" (sizeof(registers_frame_sw_t)),                               \
                         [halfframe] "I" (sizeof(registers_frame_sw_t)/2)                          \
                      : "r3","r4","r5","r6","r7","r8","r9","r11","r11");

#define LOAD_CONTEXT()                                                                             \
    __asm__ volatile ("MRS r3, PSP\n\t" /* read the process stack pointer into r3 */               \
                      "LDMIA r3!, {r4-r7}\n\t" /* these are actually r8-r11 :D */                  \
                      "MOV r8,  r4\n\t" /*                                                      */ \
                      "MOV r9,  r5\n\t" /* ...therefore they need to be copied to r8-r11        */ \
                      "MOV r10, r6\n\t" /*                                                      */ \
                      "MOV r11, r7\n\t" /*                                                      */ \
                      "LDMIA r3!, {r4-r7}\n\t" /* now we've popped r4-r7 */                        \
                      "MSR PSP, r3\n\t" /* update the real PSP */                                  \
                      ::: "r3","r4","r5","r6","r7","r8","r9","r11","r11");

/**
 * Must be used in an exception handler. Will return from the exception and continue execution
 * in thread mode (restoring context from the PSP).
 */
#define THREAD_RETURN  0xFFFFFFFD // magic: causes return to thread mode when loaded into pc
#define EXC_RET_TO_THREAD()  __asm__ volatile ("BX %[tr]\n\t" :: [tr] "r" (THREAD_RETURN))


#endif
