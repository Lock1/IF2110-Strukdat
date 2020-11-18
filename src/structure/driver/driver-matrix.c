// ---------------- Matrix Data Structure ----------------
// 13519214 / Tanur Rizaldi Rahardjo
#include "../matrix.h"
#include <stdio.h>

int main(void) {
    // Variable declaration
    matrix test;
    int row, col;

    // List creation
    printf("Row size : ");
    scanf("%d",&row);
    printf("Column size : ");
    scanf("%d",&col);
    makeMatrix(row,col,&test);

    // Input
    for (int i = 0 ; i < row ; i++) {
        for (int j = 0 ; j < col ; j++) {
            printf("%d, %d Value : ",i,j);
            scanf("%d", &entityAt(test,i,j));
        }
    }

    // Output
    for (int i = 0 ; i < row ; i++)
        for (int j = 0 ; j < col ; j++)
            printf("%d, %d : <%d>\n",i,j,entityAt(test,i,j));

    return 0;
}
