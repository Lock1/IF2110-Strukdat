//13519146 - Fadel Ananda Dotty

#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"
#include "material.h"

boolean searchMaterialByID(Material* m, int ID){
  for (int i=0; i<20; i++){
    if (m[i].ID==ID){
      return true;
    }
  }
  return false;
}

int getHargaMaterialByID(Material *m, int ID){
    for (int i=0; i<20; i++){
        if (m[i].ID==ID){
            return m[i].harga;
        }
    }
    return 0;
}

int getCountMaterialByID(Material* m, int ID) {
    for (int i=0; i<20; i++){
        if (m[i].ID==ID){
            return m[i].material_count;
        }
    }
    return 0;
}
void setCountMaterialByID(Material* m, int ID, int val) {
    for (int i=0; i<20; i++){
        if (m[i].ID==ID){
            m[i].material_count = val;
        }
    }
}
