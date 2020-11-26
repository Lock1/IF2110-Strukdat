#include <stdlib.h>
#include <stdio.h>
#include "structure/wahana.h"
#include "structure/material.h"
#include "structure/tree.h"
#include "structure/point.h"

int ReadFromWahana(Wahana** database,int materialCount);
int ReadFromBahan(Material** database);
POINT* ReadFromMap();
int MakePohonUpgrade(BinTree** database,int wahanacount);
