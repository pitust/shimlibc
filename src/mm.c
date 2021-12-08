#include <stdlib.h>
#include <string.h>

void* realloc(void* old, unsigned long newsiz) {
    if (!old) return malloc(newsiz);
    if (!newsiz) { free(old); return NULL; }
    uint64_t oldsiz = *(uint64_t*)(old - 8);
    void* nju = malloc(newsiz);
    if (!nju) { free(old); return NULL; }
    memcpy(nju, old, oldsiz < newsiz ? oldsiz : newsiz);
    memset(old, 0x41, oldsiz);
    free(old);
    return nju;
}
// print("hello world from plua!")