// -------------- List Array Data Structure --------------
// 13519214 / Tanur Rizaldi Rahardjo

// Preprocessor directive
#ifndef LISTARRAY_H
#define LISTARRAY_H

// Library
#include "boolean.h"

typedef struct lsttpl {
    char* s;
    int d;
} listTuple;

typedef struct lst {
    listTuple *data;
    int length;
    int maxIdx;
} list;

// Selector
#define length(list) (list).length
#define max(list) (list).maxIdx

#define listStr(list,idx) (list).data[(idx)].s
#define listInt(list,idx) (list).data[(idx)].d

// ----------------- Resource Management -----------------
// Create list by allocate and set length
void makeList(int len, list *ls);
// Destroy list and deallocate
void deleteList(list *ls);
// -------------------------------------------------------

// --------------------- Manipulator ---------------------
void append(list *ls, listTuple newElement);
// -------------------------------------------------------

#endif
