#ifndef _rgb2gray_h_
#define _rgb2gray_h_

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#include <stdint.h>

    uint8_t** malloc2Darray(int rows, int cols);
    void free2Darray(uint8_t** array, int rows);

    uint8_t*** malloc3Darray(int rows, int cols, int channels);
    void free3Darray(uint8_t*** array, int rows, int cols);

    void readColorRAW(const char* filename, uint8_t*** imgOUT, int rows, int cols);

    void rgb2gray(uint8_t*** imgIN, uint8_t** imgOUT, int rows, int cols);

    void saveGrayRAW(const char* filename, uint8_t** img, int rows, int cols);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _rgb2gray_h_
