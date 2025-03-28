#include "global_methods.c"
//处理low到height的元素：low为起始索引，height为结束索引
int partition(int *arr, int low, int height) {
    //将小于基准元素的值都移动到low指向的位置
    int privot = arr[low];
    int i = low + 1, j = height;
    while (i < j) {
        while (i < j && arr[j] >= privot) {
            j--;
        }
        while (i < j && arr[i] <= privot) {
            i++;
        }
        int temp = arr[j];
        arr[j] = arr[i];
        arr[i] = temp;
    }
    int temp = arr[low];
    arr[low] = arr[i];
    arr[i] = temp;
    return i;
}
//快速排序
void quick_sort(int *arr, int low, int height){
    if (arr == NULL) {
        return;
    }
    if (low < height) {
        int par_index = partition(arr, low, height);
        partition(arr, low, par_index - 1);
        partition(arr, par_index + 1, height);
    }
}

int main(){
    int arr[8] = {2, 4, 3, 6, 9, 0, 2, 8};
    quick_sort(arr, 0, 7);
    coutArray(arr, 8);
    return 0;
}
