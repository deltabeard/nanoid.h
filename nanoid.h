#pragma once
#include <stdlib.h>
#include <string.h>

#ifndef _WIN32
#include <unistd.h>
#endif

int nanoid(char *e, size_t t){
	int r;
	memset(e, 0, t);
	if(!(r = getentropy(e,t))){
		while(--t){
			*e=(*e&=63)?*e<2?45:*e<12?*e+46:*e<38?*e+53:*e+59:95;
			e++;
		}
	}
	*e = 0;
	return r;
}
