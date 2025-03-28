#include "global_methods.c"
//选择排序
void select_sort(int *arr, int len) {
    if (arr == NULL) {
        return ;
    }
    for (int i = 0; i < len; i++) {
        int min = INT_MAX;
        int index;
        //寻找后面最小的值
        for (int j = i; j < len; j++) {
            if (arr[j] < min) {
                min = arr[j];
                index = j;
            }
        }
        //处理最小值
        int temp = arr[index];
        arr[index] = arr[i];
        arr[i] = temp;
    }
}

int main(){
    int arr[8] = {2, 4, 3, 6, 9, 0, 2, 8};
    select_sort(arr, 8);
    coutArray(arr, 8);
    return 0;
}
