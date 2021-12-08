#include <printf.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <bits/deps.h>

FILE *stdin = (FILE*)-3, *stdout = (FILE*)-2, *stderr = (FILE*)-1;

void _putchar(char character) {
    __sysdep_outchar(character);
}
static void _outchr(char c, void* arg) {
    FILE* tf = arg;
    if (tf == stdin) return; // invalid op
    if (tf == stdout || tf == stderr) {
        _putchar(c);
        return;
    }
    printf("ERROR: unable to print to stream yet!\n");
    abort();
}
// we don't buffer
int fflush(FILE* f) {
    (void)f;
    return 0;
}
int fprintf(FILE* out, const char* format, ...) {
    va_list vl;
    va_start(vl, format);
    int i = fctvprintf(_outchr, (void*)out, format, vl);
    va_end(vl);
    return i;
}
size_t fwrite(const void* restrict ptr, size_t size, size_t nitems, FILE* restrict stream) {
    for (size_t i = 0; i < (size * nitems); i++) {
        _outchr(*((char*)(ptr) + i), stream);
    }
    return (size) * (nitems);
}
int getc(FILE* stream) {
    if (stream == stdin) {
        return __sysdep_getchar();
    }
    printf("ERROR: unable to read from arbitrary streams yet!\n");
    abort();
}
void* fgets(void* s, uint64_t n, FILE* stream) {
    uint8_t* data = (uint8_t*)s;
    uint64_t c = 0;
    while (c < n) {
        uint8_t chr = getc(stream);
        if (chr == '\n') {
            *data++ = '\n';
            c++;
            if (c >= n) data--;
            *data++ = 0;
            return s;
        }
        if (chr == '\x7f') {
            // backspace
            if (!c) continue;
            c--;
            *(--data) = 0;
            __sysdep_outchar('\b');
            __sysdep_outchar(' ');
            __sysdep_outchar('\b');
            continue;
        }
        *data++ = chr;
        c++;
    }
    *data++ = 0;
    return s;
}