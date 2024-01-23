#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "rgb2gray.h"

int main()
{
    const int rows = 1080, cols = 1920;

    uint8_t** imgOUT = malloc2Darray(rows, cols);
    uint8_t*** imgIN = malloc3Darray(rows, cols, 3);

    readColorRAW("imgIN.raw", imgIN, rows, cols);
    rgb2gray(imgIN, imgOUT, rows, cols);
    saveGrayRAW("imgOUT.raw", imgOUT, rows, cols);

    free3Darray(imgIN, rows, cols);
    free2Darray(imgOUT, rows);
    
    printf("EXIT_SUCCESS\n");
    return EXIT_SUCCESS;
}