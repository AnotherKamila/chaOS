#include "context_switching.h"
#include "common_memmap.h"

void *get_psp(void) {
    void *ret;
    __asm__ volatile ( "MRS %[ret], PSP" : [ret] "=r" (ret) );
    return ret;
}

void set_psp(void* sp) {
    __asm__ volatile ( "MSR PSP, %[sp]" : : [sp] "r" (sp) );
}

void prepare_task_stack(void **sp, void *start, void at_end(void)) {
    byte *newsp = *sp;

    // hw-saved frame
    newsp -= sizeof(registers_frame_hw_t);
    registers_frame_hw_t* hw_frame = (registers_frame_hw_t*)newsp;
    hw_frame->pc = make_code_addr((uintptr_t)start);
    hw_frame->lr = make_code_addr((uintptr_t)at_end); // when the task returns, we will call a routine to free its resources
    hw_frame->psr = XPSR_DEFAULT;

    // sw-saved frame
    newsp -= sizeof(registers_frame_sw_t);

    *sp = newsp;
}
