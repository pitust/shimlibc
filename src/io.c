#include <printf.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

FILE *stdin = (FILE*)-3, *stdout = (FILE*)-2, *stderr = (FILE*)-1;

static uint8_t inb(uint16_t p) {
    uint8_t o;
    asm volatile("inb %1, %0" : "=a"(o) : "Nd"(p));
    return o;
}
static void serial_tx(char a) {
    while ((inb(0x3F8 + 5) & 0x20) == 0) asm("pause");

    asm volatile("outb %%al, %%dx" ::"a"(a), "d"(0x3f8));
}
static char serial_rx() {
    while ((inb(0x3F8 + 5) & 1) == 0) asm("pause");

    char c = inb(0x3F8);
    serial_tx(c);
    if (c == '\r') {
        c = '\n';
        serial_tx('\n');
    }
    return c;
}

void _putchar(char character) {
    serial_tx(character);
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
        return serial_rx();
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
            serial_tx('\b');
            serial_tx(' ');
            serial_tx('\b');
            continue;
        }
        *data++ = chr;
        c++;
    }
    *data++ = 0;
    return s;
}