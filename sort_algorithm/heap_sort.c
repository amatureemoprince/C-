#include "global_methods.c"

void swap(int *arr, int a, int b) {
    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

void head_adjust(int *arr, int k, int len) {
    int root_val = arr[k];
    for (int i = 2 * k + 1; i < len; i = 2 * k + 1) { // 修正循环变量更新逻辑
        // 检查右孩子是否存在且是否更大
        if (i + 1 < len && arr[i] < arr[i + 1]) {
            i++;
        }
        // 若根节点大于等于子节点，调整完成
        if (root_val >= arr[i]) {
            break;
        } else {
            // 否则将子节点值上移，并继续向下调整
            arr[k] = arr[i];
            k = i;
        }
    }
    arr[k] = root_val;
}

void build_max_heap(int *arr, int len) {
    for (int i = len / 2 - 1; i >= 0; i--) {
        head_adjust(arr, i, len);
    }
}

void heap_sort(int *arr, int len) {
    build_max_heap(arr, len);
    // 只需交换 len-1 次
    for (int i = 0; i < len - 1; i++) {
        swap(arr, 0, len - i - 1);  // 将最大值交换到末尾
        head_adjust(arr, 0, len - i - 1); // 调整剩余堆
    }
}
int main() {
    int arr[6] = {3, 5, 1, 7, 0, 8};
    heap_sort(arr, 6);
    coutArray(arr, 6);
    return 0;
}