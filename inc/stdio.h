#pragma once

#include <printf.h>
#include <stdint.h>
#include <bits/file.h>

#define L_tmpnam 1024
#define BUFSIZ 1024

int remove(const char* path);
int rename(const char* old, const char* newname);

double strtod(const char*, char**);

int fprintf(FILE*, const char* format, ...);
int ferror(FILE*);
int fclose(FILE*);
int feof(FILE*);
int fseek(FILE*, long offset, int whence);
int ftell(FILE*);
int fflush(FILE*);
void* fgets(void*, uint64_t, FILE*);
FILE* fopen(const char*, const char*);
FILE* freopen(const char*, const char*, FILE*);
unsigned long fread(void*, unsigned long, unsigned long, FILE*);
unsigned long fwrite(const void*, unsigned long, unsigned long, FILE*);
char* tmpnam(char* s);
FILE* tmpfile(void);
int getc(FILE*);
void ungetc(int c, FILE*);
void clearerr(FILE*);
int setvbuf(FILE*, char*, int, size_t);
extern FILE *stdin, *stdout, *stderr;

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

#define _IONBF 0
#define _IOFBF 0
#define _IOLBF 0

#define EOF ((int)(-1))
