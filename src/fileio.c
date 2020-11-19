//13519146 - Fadel Ananda Dotty
//13519206 - M. Fawwaz Naabigh

#include <stdlib.h>
#include <stdio.h>
#include "fileio.h"

int ReadFromWahana(Wahana** database){
	FILE* file=fopen("data/wahana.txt", "r");
	if (!file)
		return 0;

	char buffer[200];
	fgets(buffer, 200, file);
	Wahana* array=(Wahana*)malloc(20*sizeof(Wahana));

	int i=0;
	while(!feof(file)){
		Wahana w;
		sscanf(buffer,"%d %s %d %d %d %s %c", &w.ID, w.nama, &w.harga, &w.durasi, &w.kapasitas, w.deskripsi, &w.gambar);
		fgets(buffer, 200, file);
		Frekuensi(w)=0;
		Penghasilan(w)=0;
		PenghasilanHari(w)=0;
		StatusWahana(w)=0;
		array[i]=w;
		i++;
	}

	fclose(file);
	*database = array;
	return i;
}

int ReadFromBahan(Material**database){
	FILE* file=fopen("data/material.txt", "r");
	if (!file)
		return 0;

	char buffer[200];
	fgets(buffer, 200, file);
	Material* array=(Material*)malloc(20*sizeof(Material));

	// while(!feof(file)){
	int i=0;
	while(!feof(file)){
		Material m;
		sscanf(buffer,"%d %s %d", &m.ID, m.nama, &m.harga);
		// printf("read wahana: %d %s %d\n", m.ID, m.nama, m.harga);
		fgets(buffer, 200, file);
		// printf("%s\n", m.nama);
		array[i]=m;
		i++;
	}
	fclose(file);
	*database = array;
	return i;
}
