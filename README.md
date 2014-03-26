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
 - run PIEs
 - crosscompiler for chaOS target (`arm-chaos-eabi-*`) - see http://wiki.osdev.org/OS_Specific_Toolchain
 - syscalls
 - switch to user mode

### Immediate TODO:

 - separate things that should be in libc into my own little libc (e.g. `memcpy`)
 - add `-nostdlib` and implement what is needed in my own little libc
 - add `-ffuncion-sections`, `-fdata-sections` and make sure my ld script is correct
 - fix GPIO (incl. # of bits for configuration)
 - tidy up that scary WIP branch, merge what you can, publish it
 - Clean up! Clean up! Clean up! (move stuff around so that it makes sense)
