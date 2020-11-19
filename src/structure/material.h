//13519146 - Fadel Ananda Dotty

#ifndef _MATERIAL_H_
#define _MATERIAL_H_

typedef struct Material{
	int ID, harga, material_count;
	char nama[999];
	char gambar;
}Material;

#define ID(M) (M).ID
#define Harga(M) (M).harga
#define Nama(M) (M).nama
#define Gambar(M) (M).gambar
#define Count(M) (M).material_count

boolean searchMaterialByID(Material* m, int ID);
int getHargaByID(Material* m, int ID);

#endif