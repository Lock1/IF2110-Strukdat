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

int getHargaById(Material *m, int ID){
    for (int i=0; i<20; i++){
        if (m[i].ID==ID){
            return m[i].harga;
        }
    }
}