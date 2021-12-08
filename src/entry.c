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

void _start() {
    entry();
    malloc_addblock(megabyte_of_dat, 1024 * 1024);
    char* argv[] = {"x86-directlua", NULL};
    exit(main(1, argv));
}