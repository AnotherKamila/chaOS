int main() {
    // TODO wrapper
    __asm__ volatile ("mov r0, #1");
    __asm__ volatile ("svc 0");
}
