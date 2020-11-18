// -------------- List Array Data Structure --------------
// 13519214 / Tanur Rizaldi Rahardjo
#include "../listarray.h"
#include <stdio.h>

int main(void) {
    // Variable declaration
    list test;
    listTuple temp;
    int listSize;

    // List creation
    printf("List size : ");
    scanf("%d",&listSize);
    makeList(listSize,&test);
    temp.s = "key";

    // Input
    for (int i = 0 ; i < listSize ; i++) {
        printf("%d. Value : ", i+1);
        scanf("%d", &temp.d);
        append(&test,temp);
    }

    // Output
    for (int i = 0 ; i < listSize ; i++)
        printf("<%s,%d>\n",listStr(test,i),listInt(test,i));

    return 0;
}
