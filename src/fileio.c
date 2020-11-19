#include <stdlib.h>
#include <stdio.h>
#include "fileio.h"

void ReadFromWahana(){
	FILE* file=fopen("wahana.txt", "r");
	if (!file)
		return;

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
}

void ReadFromBahan(){
	FILE* file=fopen("bahan.txt", "r");
	if (!file)
		return;

	char buffer[200];
	fgets(buffer, 200, file);

	while(!feof(file)){
		Material m;
		sscanf(buffer,"%d %s %d", &m.ID, m.nama, &m.harga);
		printf("read wahana: %d %s %d\n", m.ID, m.nama, m.harga);
		fgets(buffer, 200, file);
		printf("%s\n", m.nama);
	}
	fclose(file);
}
