#pragma once

extern int errno;
char* strerror(int error);

#define ENOMEM 1
#define EINVAL 2
