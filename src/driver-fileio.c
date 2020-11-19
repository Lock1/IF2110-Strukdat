#include <stdlib.h>
#include <stdio.h>
#include "../../fileio.h"

int main(){
	FILE* file=fopen("wahana.txt", "r");
	if (!file)
		return 1;

	char buffer[200];
	fgets(buffer, 200, file);

	while(!feof(file)){
		Wahana w;
		sscanf(buffer,"%d %s %d %d %d %s", &w.ID, w.nama, &w.harga, &w.durasi, &w.kapasitas, w.deskripsi);
		printf("read wahana: %d %s %d %d %d %s\n", w.ID, w.nama, w.harga, w.durasi, w.kapasitas, w.deskripsi);
		fgets(buffer, 200, file);
		printf("%s\n", w.nama);
	}
	fclose(file);

	return 0;
}
