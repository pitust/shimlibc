#pragma once

extern int errno;
char* strerror(int error);

// keep in sync with bits/errors.h
#define EOK 0
#define ENOMEM 1
#define EINVAL 2
#define EUNKERR 3
#define ENOENT 4
