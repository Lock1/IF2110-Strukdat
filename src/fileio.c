//13519146 - Fadel Ananda Dotty
//13519206 - M. Fawwaz Naabigh
// Tambah newline pada akhir

#include <stdlib.h>
#include <stdio.h>
#include "config.h"
#include "fileio.h"

int ReadFromWahana(Wahana** database){
	FILE* file=fopen("data/wahana.txt", "r");
	if (!file)
		return 0;

	char buffer[200];
	fgets(buffer, 200, file);
	Wahana* array = (Wahana*) malloc(WAHANA_MAX*sizeof(Wahana));

	int i=0;
	fgets(buffer, 200, file);
	do {
		Wahana w;
		sscanf(buffer,"%d %s %d %d %d %s %c", &w.ID, w.nama, &w.harga, &w.durasi, &w.kapasitas, w.deskripsi, &w.gambar);
		fgets(buffer, 200, file);
		Frekuensi(w)=0;
		Penghasilan(w)=0;
		PenghasilanHari(w)=0;
		StatusWahana(w)=0;
		array[i]=w;
		i++;
	} while(!feof(file));
	for(int k=0;k<i;k++){
		for(int j=0; j<200;j++){
			if (array[k].nama[j]=='-'){
				array[k].nama[j]=' ';
			}
			if(array[k].deskripsi[j]=='-'){
				array[k].deskripsi[j]=' ';
			}
		}
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
	Material* array=(Material*)malloc(BAHAN_MAX*sizeof(Material));

	// while(!feof(file)){
	int i=0;
	fgets(buffer, 200, file);
	do{
		Material m;
		sscanf(buffer,"%d %s %d", &m.ID, m.nama, &m.harga);
		// printf("read wahana: %d %s %d\n", m.ID, m.nama, m.harga);
		fgets(buffer, 200, file);
		MaterialCount(m)=0;
		// printf("%s\n", m.nama);
		array[i]=m;
		i++;
	} while(!feof(file));
	fclose(file);
	*database = array;
	return i;
}

POINT* ReadFromMap(){
	FILE* file=fopen("data/map.txt");
	if (!file)
		return 0;
	POINT* point;
	point=(POINT*)malloc(3*sizeof(POINT));
	char buffer[200];
	for (int i=0; i<3; i++){
		point[i]->x=0;
		point[i]->y=0;
	}
	for (int i=0; i<25; i++){
		fgets(buffer, 200, file);
		for(int j=0; j<50; j++){
			if(buffer[j]=='a'){
				point[i]->x=i;
				point[j]->y=j;
			}
		}
	}
	return point;
}
