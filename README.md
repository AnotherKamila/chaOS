Yes, really.

Yes, I know I'm going to fail utterly. Yes, I know it is crazy. Yes, I know I will learn a lot from my mistakes!

Introducing:

![chaOS logo](https://github.com/anotherkamila/chaOS/raw/master/logo-large.png) chaOS
=====================================================================================

**The useless, ugly and pointless OS (will-have-been-)made by a kid who thinks she's cool**

It's almost over! :D

The state right now:

- loads (almost-bare-metal) ELF binaries (compiled as PIEs and linked with my ld script)
- supports syscalls, but right now they can't take arguments (that is a TODO, along with a userspace library :D)
- preemptive multitasking (with a simple round robin scheduler) (yay!)
- can be easily ported to (at least) all Cortex MCUs, right now it works on M0 and a port to M4 is on the way
- written from scratch, including the hardware abstraction layer (CMSIS is slow and ugly!) and the needed parts of libc (why not? :D)

The truth: it can blink LEDs and needs only 1805 SLOC to do that! :P

Note: the Cortex-M4 tree is out of date and won't compile, I'll fix that when I can.

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
...

 - make a separate binary (ELF), get it in there, parse it and run it  **✔**
 - non-preemptive multitasking that actually works (i.e. deals correctly with the stack, etc.)
 - run PIEs  **✔**
 - crosscompiler for chaOS target (`arm-chaos-eabi-*`) - see http://wiki.osdev.org/OS_Specific_Toolchain
 - syscalls!  **✔** *(sort of)*
 - context switching, preemptive multitasking **✔!!!**
 - make it do something cool

### issues (TODO move to Github's issues :D)

- compile with -Wstrict-aliasing=2 and see what it says
- add restrict all over the place (specifically: memcpy)
- const-correctness (but not const-overcorrectness)
- inc/ subdir is stupid -- move those things somewhere smarter
- centralized errno.h
- move isr.h somewhere smart
- `instruction_sync_barrier` etc does not belong to nvic.h
- nvic: make interrupt the first parameter everywhere
- nvic docs don't mention whether smaller numbers are high priority or not
- maybe: use forward declarations for scary structs
- rename ARM_BLX_SHIT (:D) and make a make_thumb_addr or something
- static_assert
- syscalls with arguments => process management syscalls
- real hardfault handler
- cslibc: memcpy, memcmp etc need to copy words instead of bytes where they can
