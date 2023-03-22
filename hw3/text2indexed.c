#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char **argv) {
	if (argc != 4) {
		return -1;
	}
	
	//opening text file
	FILE* textfile = fopen(argv[1], "r");
	if (textfile == NULL) {
		exit(-1);
	}
	//opening item file to write to
	FILE* item_file = fopen(argv[2], "r");
	if (item_file == NULL) {
		exit(-1);
	}

    //opening output file
    FILE* file_output = fopen(argv[3], "w");
	if (file_output == NULL) {
		exit(-1);
	}

    long *offset_items = NULL;
    int items = 0;
    char item_l[256];
    while (fgets(item_l, 256, item_file)){
        items++;
        offset_items = (long*)realloc(offset_items, items *sizeof(long));
        offset_items[items - 1] = ftell(item_file) - strlen(item_l);
    }

    char text_l[256];

    int32_t user_id; 
	int64_t item_id;
	int8_t rating;
	int64_t timestamp;
    int64_t item_file_offset;

    while(fgets(text_l, 256, textfile)){
        sscanf(text_l, "%d %ld %hhd %ld", &user_id, &item_id, &rating, &timestamp);
        if(item_id <= items){
            item_file_offset = offset_items[item_id-1];
            fprintf(file_output,"%d %ld %d\t %ld\n", user_id, item_file_offset, rating, timestamp);
        }
    }

    free(offset_items);
	fclose(textfile);
	fclose(item_file);
    fclose(file_output);
	return 0;
}
