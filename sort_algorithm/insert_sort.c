#include "global_methods.c"

void insert_sort(int *arr, int len);
void insert_half_sort(int *arr, int len);

//插入排序:2, 4, 3, 6, 9, 0, 2, 8
void insert_sort(int *arr, int len) {
    if (arr == NULL) {
        return ;
    }
    if (len == 1) {
        return ;
    }
    int i = 1, j, cur;
    //遍历从第一个元素开始的每个元素
    for (i = 1; i < len; i++) {
        cur = arr[i];
        //从后往前检查满足条件的j位置
        for (j = i - 1; j >= 0 && arr[j] > cur; j--) {
            arr[j + 1] = arr[j];
        }
        // 赋值最前面元素
        arr[j + 1] = cur;
        //第二种实现方式
        // for (j = i - 1; j >= 0; j--) {
        //     if (arr[j] > cur) {
        //         arr[j + 1] = arr[j];
        //     }else {
        //         break;
        //     }
        // }
        // arr[j + 1] = cur;
    }
}
//折半查找
int half_find(int *arr, int val, int len) {
    if (arr == NULL) {
        return -1;
    }
    int start = 0, end = len - 1;
    int middle;
    while (start <= end) {
        middle = start + (end - start) / 2;
        if (val < arr[middle]) {
            end = middle - 1;
        }
        if (val > arr[middle]) {
            start = middle + 1;
        }
        if (val == arr[middle]) {
            return middle;
        }
    }
    return -1;
}

//查找时使用折半查找的插入排序算法
void insert_half_sort(int *arr, int len) {
    if (arr == NULL) {
        return;
    }
    int i, j, cur;
    int start, end;
    int middle;
    for (i = 1; i < len; i++) {
        cur = arr[i];
        start = 0;
        int val = cur;
        end = i - 1;
        //总是在start位置插入
        while (start <= end) {

            middle = start + (end - start) / 2;
            if (val < arr[middle]) {
                end = middle - 1;
            }
            if (val > arr[middle]) {
                start = middle + 1;
            }
            if (val == arr[middle]) {
                start = middle + 1;
            }
        }
        for (int z = i - 1; z >= start; z--) {
            arr[z + 1] = arr[z];
        }
        arr[start] = cur;
    }
}


int main(){
    int arr[8] = {2, 4, 3, 6, 9, 0, 2, 8};
    int len = sizeof(arr) / sizeof(arr[0]);
    insert_sort(arr, len);
    printf("insert_sort is:\n");
    coutArray(arr, len);
    printf("find val is 4 index is: %d\n", half_find(arr, 4, len));
    int brr[8] = {2, 4, 3, 6, 9, 0, 2, 8};
    insert_half_sort(brr, 8);
    printf("insert_half_sort is:\n");
    coutArray(brr, 8);
}
