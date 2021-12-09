#include <printf.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <bits/deps.h>

#define meta_outchar_const (FILE*)-1

FILE *stdin = NULL, *stdout = meta_outchar_const, *stderr = meta_outchar_const;

static void _writechar(FILE* file, char ch) {
	if (file == meta_outchar_const) __sysdep_outchar(ch);
	else {
		printf("todo: _writechar() to a file handle.\n");
		abort();
	}
}
void _putchar(char character) {
    _writechar(stdout, character);
}
static void _outchr(char c, void* arg) {
    FILE* tf = arg;
	_writechar(tf, c);
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
	if (!stream) {
		return -1;
	}
	printf("todo: getc() from a handle\n");
	abort();
}
void* fgets(void* s, uint64_t n, FILE* stream) {
    uint8_t* data = (uint8_t*)s;
    uint64_t c = 0;
    while (c < n) {
        int chr = getc(stream);
		if (chr < 0) {
			if (c) {
				*data++ = 0;
				return s;
			}
			return NULL;
		}
		if (chr == '\n') {
            *data++ = '\n';
            c++;
            if (c >= n) data--;
            *data++ = 0;
            return s;
        }
        if (chr == '\x7f' && (stream == meta_outchar_const || stream->_istext)) {
            // backspace
            if (!c) continue;
            c--;
            *(--data) = 0;
            continue;
        }
        *data++ = chr;
        c++;
    }
    *data++ = 0;
    return s;
}
FILE *fopen(const char *pathname, const char *mode) {
	FILE* f = (FILE*)malloc(sizeof(FILE));
	if (!f) return NULL;
	f->_canread = 0;
	f->_canwrite = 0;
	f->_hasbuffered = 0;
	f->_istext = 1;
	uint8_t plus = 0, append = 0; 
	while (*mode) {
		char m = *mode++;
		switch (m) {
			case 'r':
				f->_canread = 1;
				break;
			case 'w':
				f->_canwrite = 1;
				break;
			case '+':
				plus = 1;
				break;
			case 'a':
				f->_canwrite = 1;
				append = 1;
				break;
			case 'b':
				f->_istext = 0;
				break;
			default:
				free(f);
				return NULL;
		}
	}
	if (plus) { f->_canread = f->_canwrite = 1; }
	__sysdep_fopen(f, pathname);
}
