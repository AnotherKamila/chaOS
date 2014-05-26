// TODO: maybe I'd just be better off writing this file in assembly...

#include "stack_manip.h"

// // see Figure 9 (Cortex-M0 stack frame layout) on page 26 of the Cortex-M0 programming manual
// typedef struct {
//     word r0;
//     word r1;
//     word r2;
//     word r3;
//     word r12;
//     word lr;
//     word pc;
//     word psr;
// } registers_frame_hw_t;

// typedef struct {
//     word r4;
//     word r5;
//     word r6;
//     word r7;
//     word r8;
//     word r9;
//     word r10;
//     word r11;
// } registers_frame_sw_t;

// void exception_return_to_thread(void) __attribute__((naked));
// void exception_return_to_thread(void) {
//     __asm__ volatile ;
// }


/**
 * The following functions save and restore registers which aren't saved by hardware on interrupt
 * entry. On Cortex-M0 these are r4-r11 (the HW saves r0-r3, lr, pc, psr).
 *
 * Normally r7 is used as the frame pointer (with low optimization levels), and therefore is not
 * available to the function. In order to be able to access (and restore!) it, the
 * `-fomit-frame-pointer` option is used here.
 *
 * TODO: maybe I would be better off renaming this file to end with .S :D
 */
/*
void save_registers(void) __attribute__((optimize("omit-frame-pointer")));
void save_registers(void) {
    word sp;
    __asm__ volatile ( "MRS %[sp], PSP\n\t" // read the process stack pointer
              "STM %[sp]!, {r4-r7}\n\t" // store r4-r7 on the process stack, increment sp
              "MOV r4, r8\n\t"  //
              "MOV r5, r9\n\t"  // high registers cannot be stored to memory directly,
              "MOV r6, r10\n\t" // therefore I copy them to those that can...
              "MOV r7, r11\n\t" //
              "STM %[sp]!, {r4-r7}\n\t" // now we're actually storing r8-r11 ;)
              "MSR PSP, %[sp]\n\t" // update the real PSP
              : [sp] "=r" (sp)
              :
              : "r4","r5","r6","r7","r8","r9","r11","r11");
}

void load_registers(void) __attribute__((optimize("omit-frame-pointer")));
void load_registers(void) {
    register word sp;
    __asm__ volatile ( "MRS %[sp], PSP\n\t" // read the process stack pointer
              "LDM %[sp]!, {r4-r7}\n\t" // these are actually r8-r11 :D
              "MOV r8,  r4\n\t" //
              "MOV r9,  r5\n\t" // ...therefore they need to be copied to r8-r11
              "MOV r10, r6\n\t" //
              "MOV r11, r7\n\t" //
              "LDM %[sp]!, {r4-r7}\n\t" // now we've popped r4-r7
              "MSR PSP, %[sp]\n\t" // update the real PSP
              : [sp] "=r" (sp)
              :
              : "r4","r5","r6","r7","r8","r9","r11","r11");
}
*/

void switch_to_thread_stack(void) {
    uint32_t control;
    __asm__ volatile ("MRS %[control], CONTROL" : [control] "=r" (control));
    control |= 1<<1;
    __asm__ volatile ("MSR CONTROL, %[control]" : : [control] "r" (control));
}

void *get_msp(void) {
    void *ret;
    __asm__ volatile ( "MRS %[ret], MSP" : [ret] "=r" (ret) );
    return ret;
}

void *get_psp(void) {
    void *ret;
    __asm__ volatile ( "MRS %[ret], PSP" : [ret] "=r" (ret) );
    return ret;
}

void set_psp(void* sp) {
    __asm__ volatile ( "MSR PSP, %[sp]" : : [sp] "r" (sp) );
}

void prepare_task_stack(void **sp, void *start, void *at_end) {
    byte *newsp = *sp;

    // hw-saved frame
    newsp -= sizeof(registers_frame_hw_t);
    registers_frame_hw_t* hw_frame = (registers_frame_hw_t*)newsp;
    hw_frame->pc = (word)((uintptr_t)start | 0x1); // TODO get {,un}make_thumb_addr
    hw_frame->lr = (word)at_end; // when the task returns, we will call a routine to free its resources
    hw_frame->psr = (1<<24);

    // sw-saved frame
    newsp -= sizeof(registers_frame_sw_t);
    registers_frame_sw_t* sw_frame = (registers_frame_sw_t*)newsp;
    sw_frame->r7 = 42; sw_frame->r9 = 47; // debug :D

    *sp = newsp;
}
