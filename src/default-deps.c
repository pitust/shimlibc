#include <bits/deps.h>
#include <stdio.h>
#include <stdlib.h>

#define weak __attribute__((weak))

weak void* __sysdep_morecore(intptr_t siz) {
	printf("__sysdep_morecore(0x%llx): not implemented\n", siz);
	abort();
}
weak uint64_t __sysdep_time(void) {
    printf("__sysdep_time: not implemented\n");
    abort();
}
weak _Bool __sysdep_fopen(FILE* file, const char* path) {
    printf("__sysdep_fopen(%s): not implemented\n", path);
    abort();
}
weak void __sysdep_yield() {
    asm volatile("pause");
}
weak void __sysdep_exit(int code) {
    printf("[%s exited with code %d]\n", getprogname(), code);
    while (1) {
        __sysdep_yield();
    }
}