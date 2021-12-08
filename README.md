# shimlibc
The C library that is too portable for its own good.

At the current stage it can run several real-world applications including [lua](https://www.lua.org/).

## compiling
compile together all the files in src and musl-libm directories, with -Iinc -Imusl-libm, and you are done!

## sysdeps
you can take a look at examples/sysdeps-baremetal.c ig