#include "global_methods.c"

//冒泡排序：在有序时可能还会继续比较，浪费了资源。可以优化成有序后直接退出循环：使用一个标记
void bubbling(int *arr, int len) {
    if (arr == NULL) {
        return ;
    }

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len - 1 - i; j++) {
            int temp;
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

}
//可以提前结束冒泡排序
void bubbling_with_flag(int *arr, int len) {
    if (arr == NULL) {
        return;
    }
    for (int i = 0; i < len; i++) {
        int flag = 0;
        for (int j = 0; j < len - 1 - i; j++) {
            temp = arr[j];
            arr[j] = arr[j + 1];
            arr[j + 1] = temp;
            flag = 1;
        }
        //没有交换则直接退出
        if (flag == 0) {
            break;
        }
    }
}

int main(){
    int arr[8] = {2, 4, 3, 6, 9, 0, 2, 8};
    bubbling(arr, 8);
    coutArray(arr, 8);
    return 0;
}