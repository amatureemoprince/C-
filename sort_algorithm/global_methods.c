#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
//输出int *arr的各位元素
void coutArray(int *arr, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
