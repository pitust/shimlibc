#pragma once

#include <stdint.h>
#include <bits/file.h>

void* __sysdep_morecore(intptr_t increment);
void __sysdep_outchar(char a);
char __sysdep_getchar(void);
uint64_t __sysdep_time(void);
void __sysdep_fopen(FILE* file, const char* path);
