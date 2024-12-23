#pragma once
#include <stddef.h>

typedef int (*nanoid_getentropy_fn)(void *buffer, size_t len);

int nanoid(char *e, size_t t, nanoid_getentropy_fn f){
	int r;
	size_t i;
	for(i = 0; i < t; i++) e[i] = 0;
	if(!(r = f(e,t))){
		while(--t){
			*e=(*e&=63)?*e<2?45:*e<12?*e+46:*e<38?*e+53:*e+59:95;
			e++;
		}
	}
	*e = 0;
	return r;
}
