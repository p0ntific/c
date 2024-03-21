#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

void heapSort(int* arr, int n, int i)
{
    int max = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && *(arr + left) > *(arr + max))
    {
        max = left;
    }
    if (right < n && *(arr + right) > *(arr + max))
    {
        max = right;
    }
    if (max != i)
    {
        int tmp = *(arr + i);
        *(arr + i) = *(arr + max);
        *(arr + max) = tmp;
        heapSort(arr, n, max);
    }
}


int main()
{
    int arr[SIZE] = { 1,123,4124,4,52,35,523,423,423,234 };

    int k = (SIZE / 2) - 1;

    while (k >= 0) {
        heapSort(arr, SIZE, k);
        k -= 1;
    }

    for (int i = SIZE - 1; i >= 0; i--)
    {
        int tmp = *(arr);
        *(arr) = *(arr + i);
        *(arr + i) = tmp;
        heapSort(arr, i, 0);
    }

    for (int i = 0; i < SIZE; i++)
    {
        printf("%d ", arr[i]);
    }

    return EXIT_SUCCESS;
}