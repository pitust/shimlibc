#ifndef _WEAK_ALIAS_H
#define _WEAK_ALIAS_H

#define weak_alias(name, aliasname) \
	extern __typeof (name) aliasname __attribute__ ((weak, alias (#name)));

#endif
