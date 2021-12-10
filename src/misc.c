#include <errno.h>

int errno;

#define errmap(id, name, str) char NAME_##name[] = str;
#include <bits/errors.h>
#undef errmap

char* strerror(int error) {
#define errmap(id, name, str) if (error == id) return NAME_##name;
#include <bits/errors.h>
    return NAME_EUNKERR;
}