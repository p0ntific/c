#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define SIZE 10

bool deg_sort(int* values)
{
    static int deg = 1;
    int matrix[10][SIZE];
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            matrix[i][j] = -1;
        }
    }

    for (int i = 0; i < SIZE; i++)
    {
        int num = (values[i] % (deg * 10)) / deg;
        matrix[num][i] = values[i];
    }

    int count = 0;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (matrix[i][j] != -1)
            {
                values[count] = matrix[i][j];
                count++;
            }
        }
        if (count == SIZE && i == 0) return false;
    }
    deg *= 10;
    return true;
}


int main()
{
    int values[SIZE] = { 1,17,5,4,182,44,465,7,8,10 };

    bool is_good = true;
    while (is_good)
    {
        is_good = deg_sort(values);
    }

    for (int i = 0; i < SIZE; i++)
    {
        printf("%d ", values[i]);
    }
    return EXIT_SUCCESS;
}