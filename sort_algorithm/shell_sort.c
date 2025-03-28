#include "global_methods.c"
// 希尔排序: 根据传入的d不同会有不同的时间复杂度
void shell_sort(int *arr, int len, int d) {
    // 需要分成不同的组进行排序
    for (d; d >= 1; d = d / 2) {
        // 每组的排序的插入排序
        for (int i = d; i < len; i++) {
            int temp = arr[i];
            int j;
            // 插入排序
            for (j = i; j >= d && arr[j - d] > temp; j -= d) {
                arr[j] = arr[j - d];
            }
            arr[j] = temp;
        }
    }
}

int main() {
    int arr[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    int len = sizeof(arr) / sizeof(arr[0]);
    int d = 2;
    shell_sort(arr, len, d);
    coutArray(arr, len);
    return 0'
}