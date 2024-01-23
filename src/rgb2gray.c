#include "rgb2gray.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

uint8_t** malloc2Darray(int rows, int cols)
{
    uint8_t** array = malloc(rows * sizeof(uint8_t*));
    if (array == NULL)
    {
        perror("Error in malloc2Darray");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < rows; i++)
    {
        array[i] = malloc(cols * sizeof(uint8_t));
        if (array[i] == NULL)
        {
            perror("Error in malloc2Darray");
            exit(EXIT_FAILURE);
        }
    }

    return array;
}

void free2Darray(uint8_t** array, int rows)
{
    if (array == NULL)
    {
        fprintf(stderr, "Error in free2Darray, array == NULL\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < rows; i++)
    {
        if (array[i] == NULL)
        {
            fprintf(stderr, "Error in free2Darray, array[i] == NULL\n");
            exit(EXIT_FAILURE);
        }

        free(array[i]);
    }

    free(array);
    array = NULL;
}

uint8_t*** malloc3Darray(int rows, int cols, int channels)
{
    uint8_t*** array = malloc(rows * sizeof(uint8_t**));
    if (array == NULL)
    {
        perror("Error in malloc3Darray");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < rows; i++)
    {
        array[i] = malloc(cols * sizeof(uint8_t*));
        if (array[i] == NULL)
        {
            perror("Error in malloc3Darray");
            exit(EXIT_FAILURE);
        }

        for (int j = 0; j < cols; j++)
        {
            array[i][j] = malloc(channels * sizeof(uint8_t));
            if (array[i][j] == NULL)
            {
                perror("Error in malloc3Darray");
                exit(EXIT_FAILURE);
            }
        }
    }

    return array;
}

void free3Darray(uint8_t*** array, int rows, int cols)
{
    if (array == NULL)
    {
        fprintf(stderr, "Error in free3Darray, array == NULL\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < rows; i++)
    {
        if (array[i] == NULL)
        {
            fprintf(stderr, "Error in free3Darray, array[i] == NULL\n");
            exit(EXIT_FAILURE);
        }

        for (int j = 0; j < cols; j++)
        {
            if (array[i][j] == NULL)
            {
                fprintf(stderr, "Error in free3Darray, array[i][j] == NULL\n");
                exit(EXIT_FAILURE);
            }

            free(array[i][j]);
        }

        free(array[i]);
    }

    free(array);
    array = NULL;
}

void readColorRAW(const char* filename, uint8_t*** imgOUT, int rows, int cols)
{
    if (imgOUT == NULL)
    {
        fprintf(stderr, "Error in readColorRAW, imgOUT == NULL\n");
        exit(EXIT_FAILURE);
    }

    // fp
    FILE* fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        perror("Error in readColorRAW");
        exit(EXIT_FAILURE);
    }

    // buffer
    const size_t size = (size_t)3 * rows * cols;
    uint8_t* buffer = malloc(size * sizeof(uint8_t));
    if (buffer == NULL)
    {
        perror("Error in readColorRAW");
        exit(EXIT_FAILURE);
    }

    // Read raw file to buffer
    const size_t n = fread(buffer, sizeof(uint8_t), size, fp);
    if (n != size)
    {
        fprintf(stderr, "Error in readColorRAW, Failed to read file\n");
        exit(EXIT_FAILURE);
    }

    // buffer to imgOUT
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
        {
            int position = (c + r * cols) * 3;
            imgOUT[r][c][0] = buffer[position + 0];
            imgOUT[r][c][1] = buffer[position + 1];
            imgOUT[r][c][2] = buffer[position + 2];
        }

    // free buffer
    free(buffer);

    // close fp
    fclose(fp);
}

void rgb2gray(uint8_t*** imgIN, uint8_t** imgOUT, int rows, int cols)
{
    if (imgIN == NULL)
    {
        fprintf(stderr, "Error in rgb2gray, imgIN == NULL\n");
        exit(EXIT_FAILURE);
    }

    if (imgOUT == NULL)
    {
        fprintf(stderr, "Error in rgb2gray, imgOUT == NULL\n");
        exit(EXIT_FAILURE);
    }

    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
        {
            double R = (double)imgIN[r][c][0];
            double G = (double)imgIN[r][c][1];
            double B = (double)imgIN[r][c][2];
            imgOUT[r][c] = (uint8_t)round(R * 0.299 + G * 0.587 + B * 0.114);
        }
}

void saveGrayRAW(const char* filename, uint8_t** img, int rows, int cols)
{
    if (img == NULL)
    {
        fprintf(stderr, "Error in saveGrayRAW, img == NULL\n");
        exit(EXIT_FAILURE);
    }

    // fp
    FILE* fp = fopen(filename, "wb");
    if (fp == NULL)
    {
        perror("Error in saveGrayRAW");
        exit(EXIT_FAILURE);
    }

    // buffer
    const size_t size = (size_t)rows * cols;
    uint8_t* buffer = malloc(size * sizeof(uint8_t));
    if (buffer == NULL)
    {
        perror("Error in saveGrayRAW");
        exit(EXIT_FAILURE);
    }

    // img to buffer
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
        {
            int position = c + r * cols;
            buffer[position] = img[r][c];
        }

    // Write buffer to raw file
    const size_t n = fwrite(buffer, sizeof(uint8_t), size, fp);
    if (n != size)
    {
        perror("Error in saveGrayRAW, Failed to write file");
        exit(EXIT_FAILURE);
    }

    // free buffer
    free(buffer);

    // close fp
    fclose(fp);
}
