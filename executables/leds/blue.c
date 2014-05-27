int main() {
    // TODO wrapper
    while (1) {
        __asm__ volatile ("mov r10, %[num]" : : [num] "r" (1) );
        __asm__ volatile ("svc 0");

    }
    return 42;
}
