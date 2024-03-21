#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

void fast_sort(int* arr, int start, int end)
{
    if (start >= end) return;


    int last = *(arr + end);
    int cnt = start - 1;
    for (int i = start; i < end; i++)
    {
        if (*(arr + i) <= last)
        {
            cnt += 1;
            int tmp = *(arr + cnt);
            *(arr + cnt) = *(arr + i);
            *(arr + i) = tmp;
        }
    }

    cnt += 1;

    int tmp = *(arr + cnt);
    *(arr + cnt) = *(arr + end);
    *(arr + end) = tmp;


    fast_sort(arr, start, cnt - 1);
    fast_sort(arr, cnt + 1, end);
}

int main()
{
    int arr[SIZE] = { 51,12,242,412,2,12412,11,24,21,7 };
    fast_sort(arr, 0, SIZE - 1);

    for (int i = 0; i <= SIZE - 1; i++)
    {
        printf("%d ", arr[i]);
    }

    return EXIT_SUCCESS;
}