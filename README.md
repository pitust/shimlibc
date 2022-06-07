# shimlibc
The C library that is too portable for its own good.

At the current stage it can run several real-world applications including [lua](https://www.lua.org/).

## compiling
compile together all the files in src and musl-libm directories, with -Iinc -Imusl-libm, and you are done!

## sysdeps

There are 6 sysdeps that are currently defined.

### `void* __sysdep_morecore(intptr_t increment);`
Allocate `increment` bytes of RAM starting at the last address used and return the start address of the newly allocated region. This function will fail by default, and abort the program. Override it to use functions like malloc.

### `void __sysdep_outchar(char a);`
Output a character to a system output or log of some kind. The only sysdep which does not have a fallback.

### `void __sysdep_yield(void);`
Yields the CPU and allows another process to run. On x86, this executes `pause`. Else, it is a no-opeartion. The default case may be good enough, especially if the scheduler does not support the notion of yielding.

### `void __sysdep_exit(int code) __attribute__((noreturn));`
Exits the current process. The default implementation prints a string to stdout and calls __sysdep_yield() in an infinite loop.

### `uint64_t __sysdep_time(void);`
This sysdep should return the current time as seconds since January 1st, 1970, also known as the UNIX timestamp. The default implementation prints an error and aborts.

### `_Bool __sysdep_fopen(FILE* file, const char* path);`
This sysdep should open a file and fill out certain fields of the `FILE*` structure and return true, or set errno to the error and return false.
The fields that should be filled out are:
 - `seek_lookup` - function pointer: `mode` is one of SEEK_START, SEEK_CUR or SEEK_END. The returned value must be the offset in the file that the `offset` expands to given `pos` being the current position.
 - `read` - function pointer: Reads data from the file at a given offset and write them into the buffer. Only when there is no more data to be read can `read` return 0, and it will always indicate EOF
 - `write` - function pointer: Writes data from a buffer to a file at a given offset. The entire buffer must be written.
 - `close` - function pointer: Releases the data and other resources associated with the file descriptor.
 - `_istext` - Set this field to 1 if `\x7f` should be interpreted as a backspace.
 - `_isstream` - Set this field to `1` if there is no notion of a "stream" for this device
 - `arg` - The contents of this field will be passed into all function pointers.

You should consult these fields to determine the file mode:
 - `_canread` - Set to `1` if the file was opened for reading. Zero otherwise.
 - `_canwrite` - Set to `1` if the file was opened for writing. Zero otherwise.
