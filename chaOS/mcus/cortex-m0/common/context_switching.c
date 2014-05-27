#include "context_switching.h"

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
    hw_frame->pc = (uintptr_t)start | 0x1; // TODO get {,un}make_thumb_addr
    hw_frame->lr = (uintptr_t)at_end | 0x1; // when the task returns, we will call a routine to free its resources
    hw_frame->psr = (1<<24);

    // sw-saved frame
    newsp -= sizeof(registers_frame_sw_t);
    registers_frame_sw_t* sw_frame = (registers_frame_sw_t*)newsp;
    sw_frame->r7 = 42; sw_frame->r9 = 47; // debug :D

    *sp = newsp;
}
