#include <stdio.h>

void double_array_element(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        *(arr + i) *= 2; // here I am passing the pointer "arr" and multiplying each element in the array by 2
    }

    for (int i = 0; i < size; i++)
    {
        printf("%d ", *(arr + i));
    }
}

int main()
{
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    double_array_element(arr, size);

    printf("\n");

    return 0;
}