#include <stdio.h>
#include <stdlib.h>
#define SIZE 6


int main()
{
    int arr[SIZE] = { 7,5,4,3,2,1 };

    for (int i = 1; i < SIZE; i++)
    {
        for (int j = i - 1; j >= 0; j--)
        {
            if (arr[j] > arr[j + 1])
            {
                int tmp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = tmp;
            }
        }
    }
    for (int i = 0; i < SIZE; i++)
    {
        printf("%d\n", arr[i]);
    }
    return EXIT_SUCCESS;
}