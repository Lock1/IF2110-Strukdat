//13519146 - Fadel Ananda Dotty
//13519206 - M. Fawwaz Naabigh
// Tambah newline pada akhir

#include <stdlib.h>
#include <stdio.h>
#include "config.h"
#include "fileio.h"

int ReadFromWahana(Wahana** database, int materialCount){
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
		char *temp;
		sscanf(buffer,"%d %s %d %d %d %s %c", &w.ID, w.nama, &w.harga, &w.durasi, &w.kapasitas, w.deskripsi, &w.gambar);
		w.materialArray = (int *) malloc(materialCount*sizeof(int));
		// list L; // TODO : List ?
		// w.materialArray = makeList(materialCount, &L);
		if (w.ID < 120)
			for (int i = 0 ; i < materialCount ; i++) {
				temp = &buffer[73+i*2];
				sscanf(temp,"%d",&w.materialArray[i]);
			}

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

int MakePohonUpgrade(BinTree** database, int wahanacount){
	BinTree* array=(BinTree*)malloc(WAHANA_MAX*sizeof(BinTree));
	for(int i=0;i<(wahanacount/3);i++){
		// BinTree P = AlokNode(i+20);
		// AddDaunTerkiri(&P, 120+i);
		// AddDaun(&P,120+i,220+i,false);
		// AddDaun(&P,20+i,120+i,false);
		addrNode L = AlokNode(120+i);
	    addrNode R = AlokNode(220+i); // TODO : Upgrade
	    BinTree P = Tree(i+20, L, R);
	    array[i] = P;
	}
	*database = array;
	return wahanacount/3;
}

POINT* ReadFromMap(){
	// 0 player, 1 queue, 2 office
	FILE* file=fopen("data/map.txt","r");
	if (!file)
		return 0;
	POINT* point;
	point=(POINT*)malloc(3*sizeof(POINT));
	char buffer[200];
	for (int i=0; i<3; i++){
		Absis(point[i])=0;
		Ordinat(point[i])=0;
	}
	for (int i=0; i<25; i++){
		fgets(buffer, 200, file);
		for(int j=0; j<50; j++){
			switch(buffer[j]){
				case '@':
					Absis(point[0])=i;
					Ordinat(point[0])=j;
					break;
				case 'a':
					Absis(point[1])=i;
					Ordinat(point[1])=j;
					break;
				case 'o':
					Absis(point[2])=i;
					Ordinat(point[2])=j;
					break;
			}
		}
	}
	return point;
}
