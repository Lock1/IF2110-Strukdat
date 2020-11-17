// -------------- List Array Data Structure --------------
// 13519214 / Tanur Rizaldi Rahardjo

// Library
#include "listarray.h"
#include <stdlib.h>

// ----------------- Resource Management -----------------
// Create list by allocate and set length
void makeList(int max, list *ls) {
    length(*ls) = 0;
    max(*ls) = max;
    ls->data = (listTuple *) malloc(max*sizeof(listTuple));
}
// Destroy list and deallocate
void deleteList(list *ls) {
    max(*ls) = length(*ls) = -1;
    free(ls->data);
    ls->data = NULL;
}
// -------------------------------------------------------

// --------------------- Manipulator ---------------------
// Append new element on last list, if failed exit code 1
void append(list *ls, listTuple newElement) {
    if (length(*ls) < max(*ls))
        ls->data[length(*ls)++] = newElement;
    else
        exit(1);
}
// -------------------------------------------------------
