#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
	You are free to use any data type you like in this file.
    However, other than the five functions declared in "utils.h",
    DO NOT create any other functions.
	
*/

int cmpr_int(void *x, void *y){
	
	int x1 = *(int *)x;
	int y1 = *(int *)y;

	if(x1 == y1){
		return 0;
	}

	if(x1 > y1){
		return 1;
	}

	else{
		return -1;
	}
}

int cmpr_float(void *x, void *y) {
	
	float x1 = *(float *)x;
	float y1 = *(float *)y;

	if(x1 == y1){
		return 0;
	}

	if(x1 > y1){
		return 1;
	}

	else{
		return -1;
	}
}

void print_int(void *inter) {
	
	int* ptr = (int*)inter;
	int value = *ptr;
	printf("%d\n", value);

}

void print_float(void*floater) {
	
	float* ptr = (float*)floater;
	float value = *ptr;
	printf("%f\n", value);

}


void* read_array(char* filename, char* format, size_t* len) {
	FILE *fp;
	fp = fopen(filename, "r");
	if(fp == NULL){
		fprintf(stderr, "File failed to open.");
		exit(1);
	}

	void* array = NULL;
	int f = 0;
	char buffer[500];

	if(strcmp(format, "%d") == 0){
		array = malloc(*len *sizeof(int));
	}
	else if (strcmp(format, "%f") == 0 ){
		array = malloc(*len *sizeof(float));
	}

	if(array == NULL){
		fprintf(stderr, "Error: could not allocate memory \n");
		exit(1);
	}


	while(fgets(buffer, sizeof(buffer), fp) != NULL){
		if(strcmp(format, "%d") == 0){
			int size;
			sscanf(buffer, "%d", &size);
			((int*)array)[f] = size;
			f++;
			(*len)++;
		}
		if(strcmp(format, "%f") == 0){
			float size;
			sscanf(buffer, "%f", &size);
			((float*)array)[f] = size;
			f++;
			(*len)++;
		}

	}
	fclose(fp);
	return array; 
	free(array);
}	
