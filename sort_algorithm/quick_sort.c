#include "global_methods.c"
//处理low到height的元素：low为起始索引，height为结束索引
int partition(int *nums, int low, int high) {
    int pivot = nums[low];
    while (low < high) {
        //移动hight指针
        while (low < high && nums[high] >= pivot) {
            high--;
        }
        //填坑
        if (low < high) nums[low] = nums[high];
        while (low < high && nums[low] <= pivot) {
            low++;
        }
        //填坑
        if (low < high) nums[high] = nums[low];
    }
    //基准数放到合适的位置
    nums[low] = pivot;
    return low;
}
//快速排序
void quick_sort(int *nums, int low, int high){
    if (low < high) {
        int index = partition(nums, low, high);
        quick_sort(nums, low, index-1);
        quick_sort(nums, index+1, high);
    }
}

int main(){
    int arr[8] = {2, 5, 3, 6, 9, 0, 10, 8};
    quick_sort(arr, 0, 7);
    coutArray(arr, 8);
    int brr[8] = {2, 5, 3, 6, 9, 0, 10, 8};
    quick_sort_exchange(brr, 0, 7);
    coutArray(brr, 8);
    return 0;
}
