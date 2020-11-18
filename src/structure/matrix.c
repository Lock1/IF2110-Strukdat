// ---------------- Matrix Data Structure ----------------
// 13519214 / Tanur Rizaldi Rahardjo

// Library
#include "matrix.h"
#include <stdlib.h>

// ----------------- Resource Management -----------------
// Creating matrix by allocating and set bound
void makeMatrix (int row, int col, matrix *mat) {
    rowLen(*mat) = row;
    colLen(*mat) = col;
    mat->mtrx = (matrixTuple *) malloc(col*row*sizeof(matrixTuple));
}
// Destroy matrix and deallocate
void deleteMatrix (matrix *mat) {
    rowLen(*mat) = colLen(*mat) = -1;
    free(mat->mtrx);
    mat->mtrx = NULL;
}
// -------------------------------------------------------
