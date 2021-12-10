#ifndef errmap
#define errmap(...)
#endif

errmap(0, EOK, "Operation completed successfully")
errmap(1, ENOMEM, "The system cannot allocate the memory required")
errmap(2, EINVAL, "An invalid operation has occured")
errmap(3, EUNKERR, "An unknown error has occured")
errmap(4, ENOENT, "No such file or directory")
