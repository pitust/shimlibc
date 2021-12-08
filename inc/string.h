#pragma once

#include <ctype.h>

void* memcpy(void*, const void*, unsigned long);
int memcmp(const void*, const void*, unsigned long);
void* memchr(const void*, int, unsigned long);
void *memset(void *s, int c, unsigned long n);

unsigned long strlen(const char*);
int strncmp(const char*, const char*, unsigned long);
int strcmp(const char*, const char*);
int strcoll(const char* str1, const char* str2);
char* strchr(const char*, int);
char* strpbrk(const char*, const char*);
char* strcpy(char*, const char*);
char* strstr(const char*, const char*);
unsigned long strspn(const char*, const char*);

int tolower(int);
int toupper(int);
int isalpha(int);
int iscntrl(int);
int isdigit(int);
int isgraph(int);
int islower(int c);
int ispunct(int c);
int isspace(int c);
int isupper(int c);
int isalnum(int c);
int isxdigit(int c);
