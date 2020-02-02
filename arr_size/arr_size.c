#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int arr[] = {1, 2, 3, 4, 5};
    size_t len = sizeof(arr) / sizeof(arr[0]);

    printf("sizeof(arr) : %lu\n", sizeof(arr));
    printf("sizeof(arr[0]) : %lu\n", sizeof(arr[0]));
    printf("len : %lu\n", len);
}
