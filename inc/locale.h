#pragma once

typedef struct {
    char* decimal_point;
} locale_t;
extern locale_t _currentlocale;
#define localeconv() (&_currentlocale)

#define LC_ALL 0
#define LC_COLLATE 1
#define LC_CTYPE 2
#define LC_MONETARY 3
#define LC_NUMERIC 4
#define LC_TIME 5

static inline char* setlocale(int t, const char* loc) {
    (void)t;
    (void)loc;
    return (char*)"";
}