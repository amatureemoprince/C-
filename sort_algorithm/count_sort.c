#include <stdio.h>
#include <stdlib.h>

void counting_sort(int *arr, int len) {
    if (len <= 1) return;

    // 1. 找出最大值和最小值
    int max = arr[0], min = arr[0];
    for (int i = 1; i < len; i++) {
        if (arr[i] > max) max = arr[i];
        if (arr[i] < min) min = arr[i];
    }

    // 2. 创建计数数组（优化空间：范围是[min, max]）
    int count_size = max - min + 1;
    int *count = (int *)calloc(count_size, sizeof(int));

    // 3. 统计元素出现次数
    for (int i = 0; i < len; i++) {
        count[arr[i] - min]++; // 将数值映射到[0, count_size)区间
    }

    // 4. 累加计数（计算最终位置）
    for (int i = 1; i < count_size; i++) {
        count[i] += count[i - 1];
    }

    // 5. 反向填充结果数组（保证稳定性）
    int *output = (int *)malloc(len * sizeof(int));
    for (int i = len - 1; i >= 0; i--) {
        int val = arr[i];
        int pos = --count[val - min]; // 先减再取，对应下标从0开始
        output[pos] = val;
    }

    // 6. 拷贝回原数组
    for (int i = 0; i < len; i++) {
        arr[i] = output[i];
    }

    free(count);
    free(output);
}

// 测试代码
int main() {
    int arr[] = {4, -2, 2, 8, 8, 3, 3, 1, -5};
    int len = sizeof(arr)/sizeof(arr[0]);

    counting_sort(arr, len);

    printf("Sorted: ");
    for (int i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
    return 0;
}