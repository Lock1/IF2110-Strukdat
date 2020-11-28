// ---------------- Matrix Data Structure ----------------
// 13519214 / Tanur Rizaldi Rahardjo

// Preprocessor directive
#ifndef MATRIX_H
#define MATRIX_H

// Library
#include "boolean.h"
#include "wahana.h"

typedef struct mtrxtpl {
	boolean occupied;
	int entityType;
	Wahana* currentBuilding;
} matrixTuple;

typedef struct {
	matrixTuple *mtrx;
    int rowMax;
	int colMax;
} matrix;

// Selector
#define rowLen(M) (M).rowMax
#define colLen(M) (M).colMax
#define Elmt(M,i,j) (M).mtrx[(i)+colLen(M)*(j)]

#define occupiedAt(M,i,j) (M).mtrx[(i)+colLen(M)*(j)].occupied
#define entityAt(M,i,j) (M).mtrx[(i)+colLen(M)*(j)].entityType
#define buildingAt(M,i,j) (M).mtrx[(i)+colLen(M)*(j)].currentBuilding

// ----------------- Resource Management -----------------
// Creating matrix by allocating and set bound
void makeMatrix (int row, int col, matrix *mat);
// Destroy matrix and deallocate
void deleteMatrix (matrix *mat);
// -------------------------------------------------------

#endif
