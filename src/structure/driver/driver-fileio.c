//13519146 - Fadel Ananda Dotty
//13519206 - M. Fawwaz Naabigh

#include <stdlib.h>
#include <stdio.h>
#include "../../fileio.h"

int main(){
	Material* bahan=ReadFromBahan();
	Wahana* test=ReadFromWahana();
	for(int i=0; i<3; i++){
		printf("read material: %d %d %s\n", bahan[i].ID, bahan[i].harga, bahan[i].nama);
		printf("read wahana: %d %s %d %d %d %s %c\n", test[i].ID, test[i].nama, test[i].harga, test[i].durasi, test[i].kapasitas, test[i].deskripsi, test[i].gambar);
	}
	return 0;
}
