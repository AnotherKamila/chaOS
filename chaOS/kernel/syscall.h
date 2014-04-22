/* provides macros for defining system calls */

#ifndef KERNEL_SYSCALL_H
#define KERNEL_SYSCALL_H


#include "core.h"
/**
 * Use this if you need to refer to a syscall handler function by name. `SYSCFN(n)` resolves to
 * the internal name for the syscall number `n`.
 */
#define SYSCFN(num)  _sysc ## num

/**
 * Use this to declare syscall number `num`, named `name`, accepting the given arguments. Also
 * defines _SYSC_N_`name` as `num`.
 *
 * Arguments are typed for convenience, but they are actually passed as `void*`.
 *
 * You don't want the syscall numbers to clash. All syscalls should be declared in a single file
 * (in chaOS it is `inc/syscalls.h`) to make errors more visible (you really want to notice this
 * before the compiler does).
 *
 * To implement the syscall, you need to define function `do_name` taking the specified arguments.
 * Userspace will have the call `name` available.
 */
/*#define SYSCALL(num, name, ...)                                                                  \
        int do_ ## name (__VA_ARGS__);                                                             \
        int _sysc ## num (__VA_ARGS__) __attribute((alias("do_" ## #name)));                       \
        static const _SYSC_N_ ## name = num;
*/
#define SYSCALL(num, name)                                                                         \
        int do_ ## name (void);                                                                    \
        int _sysc ## num (void) __attribute((alias("do_" #name)));                                 \
        intern const int _SYSC_N_ ## name = num


#endif
