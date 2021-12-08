#include <locale.h>

locale_t _currentlocale;

void _init_locale() {
    _currentlocale.decimal_point = ".";
}