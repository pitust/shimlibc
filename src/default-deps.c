#include <bits/deps.h>
#include <stdio.h>
#include <stdlib.h>

#define weak __attribute__((weak))

weak void* __sysdep_morecore(intptr_t siz) {
	printf("__sysdep_morecore(0x%llx): not implemented\n", siz);
	abort();
}
weak char __sysdep_getchar(void) {
    printf("__sysdep_getchar: not implemented\n");
    abort();
}
weak uint64_t __sysdep_time(void) {
    printf("__sysdep_time: not implemented\n");
    abort();
}
