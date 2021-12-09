#pragma once

#include <stdint.h>

typedef struct FILE {
	uint8_t _istext, _canread, _canwrite, _hasbuffered;
	char buffered;
	void* arg;
	uint64_t off;

	uint64_t (*seek_lookup)(int mode, uint64_t offset);
	uint64_t (*read)(void* outbuf, void* arg, uint64_t off, uint64_t maxcnt);
	uint64_t (*write)(void* outbuf, void* arg, uint64_t off, uint64_t maxcnt);
	void (*close)(void* arg);
} FILE;

