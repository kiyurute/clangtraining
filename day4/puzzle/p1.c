#include <stdio.h>

#define TOTAL_ELEMENTS (sizeof(array) / sizeof(array[0]))
int array[] = {23,34,12,17,204,99,16};
int main()
{
    // printf("%lu\n", sizeof(array));
    // printf("%lu\n", sizeof(array[0]));
    // printf("%lu",TOTAL_ELEMENTS);

    int d;
    for(d=-1;d <= ((int)TOTAL_ELEMENTS-2);d++)
        printf("%d\n",array[d+1]);
    return 0;
}

//size_ofはバイト単位

//TOTAL_ELEMENTSの型はunsigned longだったので負の数にはなれない。しかしfor文の条件で負の数にしようとしていた。