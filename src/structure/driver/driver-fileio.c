#include <stdlib.h>
#include <stdio.h>
#include "../../fileio.h"

int main(){
	ReadFromBahan();
	Wahana* test=ReadFromWahana();
	for(int i=0; i<5; i++){
		printf("read wahana: %d %s %d %d %d %s\n", test[i].ID, test[i].nama, test[i].harga, test[i].durasi, test[i].kapasitas, test[i].deskripsi);
	}
	return 0;
}
