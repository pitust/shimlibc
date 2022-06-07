#pragma once

#include <stdint.h>
#include <stddef.h>

int system(const char* cmd);
const char* getenv(const char* env);

void* malloc(size_t size);
void free(void*);
void* realloc(void*, unsigned long);

void exit(int) __attribute__((noreturn));
void abort(void) __attribute__((noreturn));

int abs(int);

const char* getprogname(void);
void setprogname(const char *progname);

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1