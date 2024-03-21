#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

void mergeSolve(int* arr, int start, int middle, int end)
{
    const int n1 = middle - start + 1;
    const int n2 = end - middle;

    int* left = malloc(n1 * sizeof(int));
    int* right = malloc(n2 * sizeof(int));

    int i = 0;
    int j = 0;
    int k = start;

    for (int i = 0; i < n1; i++)
    {
        left[i] = *(arr + start + i);
    }

    for (int i = 0; i < n2; i++)
    {
        right[i] = *(arr + middle + 1 + i);
    }


    while (i < n1 && j < n2)
    {
        if (left[i] <= right[j])
        {
            *(arr + k) = left[i];
            i++;
        }
        else
        {
            *(arr + k) = right[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        *(arr + k) = left[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        *(arr + k) = right[j];
        j++;
        k++;
    }
    free(left);
    free(right);
}

void mergeSort(int* arr, int start, int end)
{
    if (start >= end) return;

    int middle = (start + end) / 2;
    mergeSort(arr, start, middle);
    mergeSort(arr, middle + 1, end);

    mergeSolve(arr, start, middle, end);
}

int main()
{
    int arr[SIZE] = { 1,421,122,745,55,112,523,4,55,6 };

    mergeSort(arr, 0, SIZE - 1);

    for (int i = 0; i < SIZE; i++)
    {
        printf("%d ", arr[i]);
    }

    return EXIT_SUCCESS;
}