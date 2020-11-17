// ---------------- Matrix Data Structure ----------------
// 13519214 / Tanur Rizaldi Rahardjo

// Preprocessor directive
#ifndef MATRIX_H
#define MATRIX_H

// Library
#include <stdlib.h>
#include "boolean.h"
#include "listarray.h"

typedef struct {
	list *Mem;
    int rowMax;
	int colMax;
} matrix;

// Selector
#define rowLen(M) (M).rowMax
#define colLen(M) (M).colMax
#define Elmt(M,i,j) (M).Mem[(i)+colLen(M)*(j)]



// ----------------- Resource Management -----------------
// Creating matrix by allocating and set bound
void makeMatrix (int row, int col, matrix *mat);
// Destroy matrix and deallocate
void deleteMatrix (matrix *mat);
// -------------------------------------------------------

#endif
