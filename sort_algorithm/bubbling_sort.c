#include "global.c"
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
int main(){
    int arr[8] = {2, 4, 3, 6, 9, 0, 2, 8};
    bubbling(arr, 8);
    coutArray(arr, 8);
    return 0;
}