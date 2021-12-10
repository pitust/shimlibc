#pragma once

#include <stdint.h>
#include <bits/file.h>

void* __sysdep_morecore(intptr_t increment);
void __sysdep_outchar(char a);
uint64_t __sysdep_time(void);
_Bool __sysdep_fopen(FILE* file, const char* path);
