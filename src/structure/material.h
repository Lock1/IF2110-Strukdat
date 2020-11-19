//13519146 - Fadel Ananda Dotty

#ifndef _MATERIAL_H_
#define _MATERIAL_H_

typedef struct Material{
	int ID, harga;
	char nama[999];
	char gambar;
}Material;

#define ID(M) (M).ID
#define Harga(M) (M).harga
#define Nama(M) (M).nama
#define Gambar(M) (M).gambar

boolean searchMaterialByID(Material* w, int ID);

#endif