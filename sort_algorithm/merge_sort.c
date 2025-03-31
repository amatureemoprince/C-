#include "global_methods.c"
// 合并函数（新增临时数组参数）
void merge(int *arr, int low, int mid, int high) {
    // 创建临时数组
    int *temp = malloc((high - low + 1) * sizeof(int));
    int i = low;        // 左子数组起点
    int j = mid + 1;    // 右子数组起点
    int k = 0;          // 临时数组索引
    // 合并两个有序子数组
    while (i <= mid && j <= high) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }
    // 处理剩余元素
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= high) temp[k++] = arr[j++];
    // 将排序结果拷贝回原数组
    for (int m = 0; m < k; m++) {
        arr[low + m] = temp[m];
    }
    free(temp);
}

void merge_sort(int *arr, int low, int high) {
    if (low < high) {
        int mid = low + (high - low)/2;
        merge_sort(arr, low, mid);
        merge_sort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}

int main() {
    int arr[6] = {3, 5, 1, 7, 0, 8};
    merge_sort(arr, 0, 5);  // 修正：high应为5（最后一个元素索引）
    coutArray(arr, 6);
    return 0;
}