#include <math.h>
// #include "weak_alias.h"
//#include "libc.h"

double remainder(double x, double y)
{
	int q;
	return remquo(x, y, &q);
}

