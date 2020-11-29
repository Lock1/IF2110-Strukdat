//13519146 - Fadel Ananda Dotty

#ifndef _MATERIAL_H_
#define _MATERIAL_H_

typedef struct Material{
	int ID, harga, material_count;
	char nama[999];
}Material;

#define MaterialID(M) (M).ID
#define MaterialHarga(M) (M).harga
#define MaterialNama(M) (M).nama
#define MaterialCount(M) (M).material_count

boolean searchMaterialByID(Material* m, int ID);
int getHargaMaterialByID(Material* m, int ID);
int getCountMaterialByID(Material* m, int ID);
void setCountMaterialByID(Material* m, int ID, int val);

#endif
