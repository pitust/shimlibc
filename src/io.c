#include <printf.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <bits/deps.h>

#define meta_outchar_const (FILE*)-1

FILE *stdin = NULL, *stdout = meta_outchar_const, *stderr = meta_outchar_const;

static void _writechar(FILE* file, char ch) {
	errno = 0;
	if (file == meta_outchar_const) __sysdep_outchar(ch);
	else {
		if (!file->_canwrite) {
			errno = EINVAL;
			return;
		}
		if (file->_isstream) {
			file->write(file->arg, &ch, 0, 1);
		} else {
			int64_t wr = file->write(file->arg, &ch, file->off, 1);
			if (wr < 0) return;
			file->off += wr;
		}
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
	errno = 0;
    for (size_t i = 0; i < (size * nitems); i++) {
        _outchr(*((char*)(ptr) + i), stream);
    }
    return (size) * (nitems);
}
int getc(FILE* stream) {
	errno = 0;
	if (!stream) {
		errno = EINVAL;
		return -1;
	}
	uint8_t buf = 0;
	if (stream->_isstream) {
		intptr_t i = stream->read(stream->arg, &buf, 0, 1);
		if (i <= 0) return -1;
		return buf;
	} else {
		intptr_t i = stream->read(stream->arg, &buf, stream->off, 1);
		if (i <= 0) return -1;
		stream->off += i;
		return buf;
	}
}
void* fgets(void* s, uint64_t n, FILE* stream) {
	errno = 0;
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
	errno = 0;
	FILE* f = (FILE*)malloc(sizeof(FILE));
	if (!f) {
		errno = ENOMEM;
		return NULL;
	}
	f->_canread = 0;
	f->_canwrite = 0;
	f->_hasbuffered = 0;
	f->_istext = 0;
	f->_isstream = 0;
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
			default:
				free(f);
				errno = EINVAL;
				return NULL;
		}
	}
	if (plus) { f->_canread = f->_canwrite = 1; }
	if (__sysdep_fopen(f, pathname)) {
		if (f->_isstream && append) {
			f->close(f->arg);
			free(f);
			errno = EINVAL;
			return NULL;
		}
		if (append) f->off = f->seek_lookup(SEEK_END, 0, 0);
		else f->off = 0;
	} else {
		free(f);
		if (!errno) errno = EUNKERR;
		return NULL;
	}
	return f;
}
