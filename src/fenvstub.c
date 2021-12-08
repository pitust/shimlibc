#include <fenv.h>
#include <stdio.h>
#include <stdlib.h>

__attribute__((noreturn))
static void fenvstub(const char* nam) {
    printf("fenvstub: reached %s!\n", nam);

    abort();
}

#define stub(nam) { fenvstub(#nam); }

int feclearexcept(int _0) stub(feclearexcept)
int fegetenv(fenv_t * _0) stub(fegetenv)
int fegetexceptflag(fexcept_t * _0, int _1) stub(fegetexceptflag)
int fegetround(void) stub(fegetround)
int feholdexcept(fenv_t * _0) stub(feholdexcept)
int feraiseexcept(int _0) stub(feraiseexcept)
int fesetenv(const fenv_t * _0) stub(fesetenv)
int fesetexceptflag(const fexcept_t * _0, int _1) stub(fesetexceptflag)
int fesetround(int _0) stub(fesetround)
int fetestexcept(int _0) stub(fetestexcept)
int feupdateenv(const fenv_t * _1) stub(feupdateenv)
