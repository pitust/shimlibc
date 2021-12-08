#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

char* strchr(const char* s, int c) {
    size_t i = 0;
    while (s[i]) {
        if (s[i] == c) return (char*)(&s[i]);
        i++;
    }
    if (c == 0) return (char*)(&s[i]);
    return NULL;
}

int strcoll(const char* a, const char* b) {
    // TODO: strcoll should take "LC_COLLATE" into account.
    return strcmp(a, b);
}

char* strpbrk(const char* s, const char* chrs) {
    size_t n = 0;
    while (s[n]) {
        if (strchr(chrs, s[n])) return (char*)(s + n);
        n++;
    }
    return NULL;
}

size_t strspn(const char* s, const char* chrs) {
    size_t n = 0;
    while (true) {
        if (!s[n] || !strchr(chrs, s[n])) return n;
        n++;
    }
}
char* strstr(const char* s, const char* pattern) {
    for (size_t i = 0; s[i]; i++) {
        bool found = true;
        for (size_t j = 0; pattern[j]; j++) {
            if (!pattern[j] || s[i + j] == pattern[j]) continue;

            found = false;
            break;
        }

        if (found) return (char*)(&s[i]);
    }

    return NULL;
}