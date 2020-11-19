//13519146 - Fadel Ananda Dotty
//13519206 - M. Fawwaz Naabigh

#include <stdlib.h>
#include <stdio.h>
#include "fileio.h"

Wahana* ReadFromWahana(){
	FILE* file=fopen("data/wahana.txt", "r");
	if (!file)
		return NULL;

	char buffer[200];
	fgets(buffer, 200, file);
	Wahana* array=(Wahana*)malloc(20*sizeof(Wahana));
	JumlahTotal(w)=0;

	for(int i=0; !feof(file); i++){
		Wahana w;
		sscanf(buffer,"%d %s %d %d %d %s %c", &w.ID, w.nama, &w.harga, &w.durasi, &w.kapasitas, w.deskripsi, &w.gambar);
		fgets(buffer, 200, file);
		Frekuensi(w)=0;
		Penghasilan(w)=0;
		PenghasilanHari(w)=0;
		StatusWahana(w)=0;
		JumlahTotal(w)++;
		array[i]=w;
	}
	for(int i=0;i<200;i++){
		for(int j=0; j<200;j++){
			if (array[i].nama[j]=='-'){
				array[i].nama[j]=' ';
			}
			if(array[i].deskripsi[j]=='-'){
				array[i].deskripsi[j]=' ';
			}
		}
	}
	fclose(file);
	return array;
}

Material* ReadFromBahan(){
	FILE* file=fopen("data/material.txt", "r");
	if (!file)
		return NULL;

	char buffer[200];
	fgets(buffer, 200, file);
	Material* array=(Material*)malloc(20*sizeof(Material));

	// while(!feof(file)){
	for(int i=0; !feof(file); i++){
		Material m;
		sscanf(buffer,"%d %s %d", &m.ID, m.nama, &m.harga);
		// printf("read wahana: %d %s %d\n", m.ID, m.nama, m.harga);
		fgets(buffer, 200, file);
		// printf("%s\n", m.nama);
		array[i]=m;
	}
	fclose(file);
	return array;
}
