/**
 * 王道课后习题
 *第二章:线性表
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
/**
 * 第一题
 */
int findMin(int* arr, int *len) {
    if (arr == NULL) {
        fprintf(stderr, "arr is the NULL");
        exit(1);
    }
    int min = arr[0];
    int index = 0;
    for (int i = 0; i < *len; i++) {
        if (arr[i] < min) {
            index = i;
            min = arr[i];
        }
    }
    for (int i = index; i < *len; i++) {
        arr[i] = arr[i + 1];
    }
    (*len)--;
    return min;
}
void minePrintf(const char *info) {
    printf(info);
    printf("==========================================================");
    printf("\n");
}

/**
 * 第二题
 */
void reserver(int *arr, const int len) {
    int first = 0;
    int end = len - 1;
    while (first < end) {
        const int temp = arr[first];
        arr[first] = arr[end];
        arr[end] = temp;
        first++;
        end--;
    }
}

/**
 * 第三题
 */
void deleteSample(int *arr, int *len, const int x) {
    int k = 0;
    for (int i = 0; i < *len; i++) {
        if (arr[i] != x) {
            arr[k++] = arr[i];
        }
    }
    (*len) = k;
}

/**
 * 第四题
 */
void deleteRange(int *arr, const int t, const int s, int *len) {
    if (arr == NULL) {
        fprintf(stderr, "arr is the NULL");
        exit(1);
    }
    if (t >= s) {
        fprintf(stderr, "s must bigger than t");
        exit(1);
    }
    int k = 0;
    for (int i = 0; i < (*len); i++) {
        if (arr[i] > s || arr[i] < t) {
            arr[k++] = arr[i];
        }
    }
    (*len) = k;
}

/**
 * 第五题
 */
void deleteAllSample(int *arr, int *len) {
    if (arr == NULL) {
        fprintf(stderr, "arr is the NULL");
        exit(1);
    }
    for (int i = 0; i < *len; i++) {
        int index = i + 1;
        for (int j = i + 1; j < *len; j++) {
            if (arr[i] != arr[j]) {
                arr[index++] = arr[j];
            }
        }
        (*len) = index;
    }
}

/**
 * 第六题
 */
int* sort(const int *arr, const int *brr, const int len_a, const int len_b) {
    if (arr == NULL || brr == NULL) {
        fprintf(stderr, "One of the arrays is NULL\n");
        exit(1);
    }
    int *result = (int *)malloc(sizeof(int) * (len_a + len_b));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    int start_a = 0, start_b = 0, index = 0;
    while (start_a < len_a && start_b < len_b) {
        if (arr[start_a] <= brr[start_b]) {
            result[index++] = arr[start_a++];
        } else {
            result[index++] = brr[start_b++];
        }
    }
    while (start_a < len_a) {
        result[index++] = arr[start_a++];
    }
    while (start_b < len_b) {
        result[index++] = brr[start_b++];
    }
    return result;
}

/**
 * 第七题
 */
//这个需要重新写一下这个反转函数，连续两次反转就可以实现两个数组的反转了，下面只是思路不是真正的代码
void reserverTwo(int *arr, const int len_a, const int len_b) {
    reserver(arr, len_a);
    reserver(arr, len_b);
    reserver(arr, len_b + len_b);
}

/**
 * 第八题
 */
void exchangeOrInsert(int *arr, const int len, int val) {
    int first = 0, end = len - 1;
    int mid = 0;
    while (first <= end) {
        mid = first + (end - first) / 2;
        if (arr[mid] == val) break;
        if (arr[mid] < val) first = mid + 1;
        if (arr[mid] > val) end = mid - 1;
    }
    if (arr[mid] == val && mid != len - 1) {
        int temp = arr[mid];
        arr[mid] = arr[mid + 1];
        arr[mid] = temp;
    }
    if (first > end) {
        for (int i = len - 1; i > end; i--) {
            arr[i + 1] = arr[i];
        }
        arr[end + 1] = val;
    }
}

int three_max(int i, int i1, int i2) {
    int max = (i >= i1) ? i : i1;
    return (max > i2) ? max : i2;
}

/**
 * 第九题
 */
void findSample(const int *arr, int *brr, const int *crr, const int len) {
    int i = 0, j = 0, k = 0, index = 0;
    while (i < len && j < len && k < len) {
        if (arr[i] == brr[j] == crr[k]) {
            i++;
            j++;
            k++;
            printf("%d\n", arr[i]);
        }else {
            int max = three_max(arr[i], brr[j], crr[k]);
            if (arr[i] < max) i++;
            if (brr[j] < max) j++;
            if (crr[k] < max) k++;
        }
    }
}
    int main(void) {
        //第一题测试
        int arr[5] = {3, 1, 4, 5, 7};
        int len = 5;
        minePrintf("fist test:");
        printf("the min number is %d\nthe arr is :", findMin(arr, &len));
        for (int i = 0; i < len; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
        //第二题测试
        minePrintf("second test:");
        int brr[5] = {3, 1, 4, 5, 7};
        printf("the origin brr is : 3, 1, 4, 5, 7\n");
        reserver(brr, 5);
        printf("the result brr is : ");
        for (int i = 0; i < 5; i++) {
            printf("%d, ", brr[i]);
        }
        printf("\n");
        minePrintf("third test: ");
        int crr[5] = {12, 4 , 4, 21, 4};
        int len2 = 5;
        printf("the origin crr is : 12, 4 , 4, 21, 4\n");
        deleteSample(crr, &len2, 4);
        printf("the result brr is : ");
        for (int i = 0; i < len2; i++) {
            printf("%d, ", crr[i]);
        }
        printf("\n");
        minePrintf("fourth test: ");
        int drr[5] = {12, 22, 23, 44, 56};
        int len3 = 5;
        printf("the origin drr is : 12, 22, 23, 44, 56\n");
        deleteRange(drr, 22, 44, &len3);
        printf("the result is : ");
        for (int i = 0; i < len3; i++) {
            printf("%d, ", drr[i]);
        }
        printf("\n");
        minePrintf("fifth test: ");
        int err[5] = {12, 33, 12, 33, 1};
        int len4 = 5;
        printf("the origin err is: 12, 33, 12, 33, 1\n");
        deleteAllSample(err, &len4);
        printf("the result is: ");
        for (int i = 0; i < len4; i++) {
            printf("%d, ", err[i]);
        }
        printf("\n");
        minePrintf("sixth test: ");
        const int frr[5] = {12, 22, 32, 41, 44};
        const int grr[5] = {6, 21, 40, 67, 77};
        printf("the origin two array is\nfrr: 12, 22, 32, 41, 44\ngrr: 6, 21, 40, 67, 77\n");
        int * sort1 = sort(frr, grr, 5, 5);
        printf("after sort is : ");
        for (int i = 0; i < 10; i++) {
            printf("%d ,", sort1[i]);
        }
        free(sort1);
        return 0;
    }