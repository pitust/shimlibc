#include <time.h>
#include <bits/deps.h>

time_t time() { return __sysdep_time(); }