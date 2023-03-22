#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {
	if (argc != 3) {
		fprintf(stderr, "Wrong number of command-line arguments\n");
		return -1;
	}
	
	//opening input file
	FILE* file_input = fopen(argv[1], "r");
	if (file_input == NULL) {
		exit(-1);
	}
	//opening output file to write to
	FILE* file_output = fopen(argv[2], "wb");
	if (file_output == NULL) {
		exit(-1);
	}

	char buffer[32];
	int32_t user_id; 
	int16_t item_id;
	int8_t rating;
	int64_t timestamp; 


	//write and populate files
	while(fgets(buffer, 32,  file_input) != NULL){

		sscanf(buffer, "%d %hd %hhd %ld", &user_id, &item_id, &rating, &timestamp);

		// printf("User ID: %d, Item ID: %d, Rating: %d, Timestamp %ld\n", user_id, item_id, rating, timestamp);

		fwrite(&user_id, sizeof(user_id), 1, file_output);
		fwrite(&item_id, sizeof(item_id), 1, file_output);
		fwrite(&rating, sizeof(rating), 1, file_output);
		fwrite(&timestamp, sizeof(timestamp), 1, file_output);

	}

	fclose(file_input);
	fclose(file_output);
	return 0;
}
