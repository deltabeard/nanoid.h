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
			*e=(*e&=63)<10?*e+48:*e<36?*e+87:*e<46?*e+12:*e<62?*e+19:*e>62?45:95;
			e++;
		}
	}
	*e = 0;
	return r;
}
