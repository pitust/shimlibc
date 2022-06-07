#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv);

void __libc_start_main(int argc, char** argv) {
    char* arg = argv[0];
    char* pname = argv[0];
    while (*arg) {
        if (*arg++ == '/') pname = arg;
    }
    char progname[strlen(pname) + 1];
    strcpy(progname, pname);
    setprogname(progname);

    exit(main(argc, argv));
}

static const char* progname;
void setprogname(const char* name) {
    progname = name;
}
const char* getprogname(void) {
    return progname;
}
