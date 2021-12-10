#pragma once

#include <stdint.h>

typedef struct FILE {
	uint8_t _istext, _canread, _canwrite, _hasbuffered, _isstream;
	char buffered;
	void* arg;
	uint64_t off;

	uint64_t (*seek_lookup)(int mode, uint64_t offset);
	int64_t (*read)(void* arg, void* buf, uint64_t off, uint64_t maxcnt);
	int64_t (*write)(void* arg, const void* buf, uint64_t off, uint64_t maxcnt);
	void (*close)(void* arg);
} FILE;

