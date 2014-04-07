Yes, really.

Yes, I know I'm going to fail utterly. Yes, I know it is crazy. Yes, I know I will learn a lot from my mistakes!

Introducing:

![chaOS logo](https://github.com/anotherkamila/chaOS/raw/master/logo-large.png) chaOS
=====================================================================================

**The useless, ugly and pointless OS (will-have-been-)made by a kid who thinks she's cool**

The plan:
---------

I will target ARM Cortex-M0, because it is not too simple (i.e. scary enough to look like the real thing) and still better than Intel/AMD.
For now no multitasking or anything is planned, I will be satisfied if I can run a nice binary in user mode with syscalls (where by "nice" I mean compiled for this thing instead of bare metal).

Later I might add some form of (preemptive) multitasking => real memory management, a scheduler, peripherals management and who knows what else. At this stage I will probably decide to make it a real-time OS, just because I can. Yes, and one day I might add my own malloc and filesystem (since I am going to code those in school anyway)! And of course create my own libc while we're at it. But most probably I won't.

Progress:
---------

It can load (almost-bare-metal) ELF binaries and run them (but only from a fixed address - PIEs are a TODO). I need sleep.

How to add support for other ARM CPUs
-------------------------------------

For basic support three files need to be added:

- ld script (`devices/<CPU>.ld`): specifies memory layout
- CPU-specific header with constants, register mappings, peripherals etc. (`devices/<CPU>.h`)
- ISR vector table layout (`devices/<CPU>-isr_vector.c`)

See `devices/stm32f0*` for examples.

`make` then needs to be called specifying the CPU and (optionally) CPU family (like `make CPUFAMILY=cortex-m0 CPU=stm32f0`, which are the defaults).

Of course, every MCU has a different set of peripherals accessed in different ways. Once I actually need to support more MCUs, I will specify how to make CPU-specific peripherals drivers.

Side note: I have not tested it :D (But it seems to at least compile cleanly for different families.)

----------------------------------------------------------------------------

Unless you are interested in what I think I know and what I think I should do, do not read any further. Also, if you think what I think I know is wrong, please please please let me know.

"notes.txt"
-----------

Right now I have a STM32F051R8 MCU (on a Discovery board). That might or might not change in the future.

No Cortex-M MCUs have an MMU. The M4 is the only one with an MPU (so yes, my current HW or anything I could easily upgrade to won't have virtual memory, and my current HW won't have any form of memory protection (which makes all the user-mode stuff somewhat useless, but hey, it's just for learning purposes.)) Using a CPU instead of an MCU sounds scary to me, so I am planning to live with that.

### TODO:

 - figure out:
   - how to run two things without an MMU  **✔**
   - where to run my programs from and how to do it (flash/RAM/external data storage?)  **✔**
 - crosscompiler for bare metal target (`arm-none-eabi-*`)  **✔**
 - blink LEDs  **✔**
 - find out how to setup remote debugging with gdb  **✔**
 - blink LEDs with complete understanding and control of what happened  **✔**
   - write a correct ld script  **✔**
   - avoid the library (note: is that NIH or is it actually a good idea for a change?)  **✔**
 - communication with SD card
 - stop ignoring processor startup procedure at some point

...

 - make a separate binary (ELF), get it in there, parse it and run it  **✔**
 - non-preemptive multitasking that actually works (i.e. deals correctly with the stack, etc.)
 - run PIEs  **✔**
 - crosscompiler for chaOS target (`arm-chaos-eabi-*`) - see http://wiki.osdev.org/OS_Specific_Toolchain
 - syscalls!
 - switch to user mode (but apparently not on this MCU :D)
 - context switching, preemptive multitasking (:D)

### Immediate TODO:

 - move code from .h into .c + change `static` to `intern` now that I have it
 - malloc
 - throw gpio.h into a black hole
 - tidy up that scary WIP branch, merge what you can, publish it
 - use two separate stacks

### Where to go next

 - TODO think about what to think about :D (w/ regards to how I want to use this) \*
 - implement syscalls
 - context switching --> preemptive multitasking! (TODO think about the scheduler -- round robin (perhaps prioritized)?) \*
 - are things like `malloc` or linker in kernel? \*
 - filesystem (sffs -- stupid flash filesystem? i.e. something read-only -- minimum of code & space overhead, zero worrying about SD card, filesystem creation via cat, etc.; and if it is on flash, it doesn't actually need an API, since it's direct memory access :D)
 - init mechanism :D
