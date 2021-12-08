#include "printf.h"
#include "stdlib.h"
 
 __attribute__((noreturn))
void exit(int ec) {
    printf("[plua exited with code %d]\n", ec);
    while (1) {
        asm volatile("cli; hlt");
    }
}
__attribute__((noreturn))
void abort() {
    printf("ERROR: aborted!\n");
    exit(1);
}
int system(const char *cmd) {
    printf("$ %s\ncan't do system()\n", cmd);
    return 1;
}

int abs(int i) {
    return i < 0 ? -i : i;
}