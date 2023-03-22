#include "insertion.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/*
	We emphasize this: because this is a generic implementation, in insertion.c you must not use if-else to
	discriminate different data types in your code. Your code must be able to deal with any data type possible.
	Therefore, we limit the usage of the following primitive types:
	- int or size_t: only allowed as loop iterators;
	- char or u_int8_t: can be used as you wish;
	- Types that are used in the declarations of iSort() and iPrint(): feel free to use them for their _original_
      purpose;
	- All other types are not allowed to appear in insertion.c: no exceptions, no matter if you actually used
	  them, or what purpose it is. Once it appears, you will receive 30% reduction of the homework.

	You are free to create helper functions only in insertion.c; you must declare and implement them in the
    .c file instead of the header files. Do not change any of the header files.
	
*/


void iSort(void* base, size_t nel, size_t width, int (*compare)(void*,void*)) {
 	char* arrayHelper = (char*) malloc (width);
	int i, k;
	char* array = (char*) base;

	for(i = 1; i < nel; i++){
		k = i;
		for(k = i; k > 0; k--){
			if(compare(array+(k-1)*width, array+k*width) > 0){
				memcpy(arrayHelper, array+(k-1)*width, width);
				memcpy(array+(k-1)*width, array+k*width, width);
				memcpy(array+k*width, arrayHelper, width);
			}
		}
	}
	free(arrayHelper);

}

void iPrint(void* base, size_t nel, size_t width, void (*print)(void*)) {
	// print("test");
	
	char* txt = base;
	for (size_t i = 0; i < nel; i++){
		print(txt);
		txt += width; 
	}	
	
}