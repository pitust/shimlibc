#include <bits/deps.h>

#ifdef __clang__
#pragma GCC diagnostic ignored "-Wmacro-redefined"
#endif

#define USE_LOCKS 1
#define USE_SPIN_LOCKS 1
#define HAVE_MORECORE 1
#define MORECORE __sysdep_morecore
#define MORECORE_CANNOT_TRIM
#define HAVE_MMAP 0
#define HAVE_MREMAP 0
#define MMAP_CLEARS 0
#define LACKS_UNISTD_H
#define LACKS_SYS_TYPES_H
#define LACKS_SYS_PARAM_H
#define LACKS_SYS_MMAN_H
#define LACKS_STRINGS_H
#define LACKS_SCHED_H
#define LACKS_TIME_H // well we have it, but our impl actually sucks
#include <bits/_dlmalloc.h>
