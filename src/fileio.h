#include <stdlib.h>
#include <stdio.h>
#include "structure/wahana.h"
#include "structure/material.h"
#include "structure/tree.h"
#include "structure/point.h"

int ReadFromWahana(Wahana** database);
int ReadFromBahan(Material** database);
POINT* ReadFromMap();
void MakePohonUpgrade(BinTree** database,int wahanacount);
