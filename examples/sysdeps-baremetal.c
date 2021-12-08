#include <malloc.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>

int errno;

int main(int argc, char** argv);

#define STACKSIZE (1024*1024)

uint16_t stack[STACKSIZE];
__attribute__((section(".stivale2hdr"))) uint64_t hdr[4] = {0, (uint64_t)&stack[STACKSIZE] };

void entry();

static uint8_t megabyte_of_dat[1024 * 1024];

static uint8_t inb(uint16_t p) {
    uint8_t o;
    asm volatile("inb %1, %0" : "=a"(o) : "Nd"(p));
    return o;
}
void __sysdep_outchar(char a) {
    while ((inb(0x3F8 + 5) & 0x20) == 0) asm("pause");

    asm volatile("outb %%al, %%dx" ::"a"(a), "d"(0x3f8));
}
char __sysdep_getchar(void) {
    while ((inb(0x3F8 + 5) & 1) == 0) asm("pause");

    char c = inb(0x3F8);
    __sysdep_outchar(c);
    if (c == '\r') {
        c = '\n';
        __sysdep_outchar('\n');
    }
    return c;
}

void _start() {
    asm("movq %cr0, %rax\n"
    "andq $0xFFFB, %rax\n"
    "orq $0x2, %rax\n"
    "movq %rax, %cr0\n"
    "movq %cr4, %rax\n"
    "orq 3 << 9, %rax\n"
    "movq %rax, %cr4\n");
    malloc_addblock(megabyte_of_dat, 1024 * 1024);
    char* argv[] = {"whatever", NULL};
    exit(main(1, argv));
}

