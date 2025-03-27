// #include<stdio.h>
// #include<limits.h>
// #include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

int search(int *arr, int len, int val){
	int left = 0;
	int right = len - 1;
	while(left <= right){
		int middle = left + (right - left) / 2;
		if(arr[middle] < val){
			left = middle + 1;
		}else if(arr[middle] > val){
			right = middle - 1;
		}else{
			return middle;
		}
	}
	return -1;
}

int delete_sample_element(int *arr, int val, int len){
	int low_index = 0;
	for(int fast_index = 0; fast_index < len; fast_index++){
		if(arr[fast_index] != val){
			arr[low_index++] = arr[fast_index];
		}
	}
	return low_index;
}
int* sortedSquares(int *arr, int len){
	int k = len - 1;
	int i = 0;
	int j = len - 1;
	int* result = (int *)malloc(sizeof(int) * len);
	for(i, j; i < j;){
		if(arr[i] * arr[i] < arr[j] * arr[j]){
			result[k--] = arr[j] * arr[j];
			j--;
		}else{
			result[k--] = arr[i] * arr[i];
			i++;
		}
	}
	return result;
}

int minSubArrayLen(int *arr, int s, int len){
	int result = INT_MAX;
	int num = 0;
	int subLen = 0;
	int i = 0;
	for(int j = 0; j < len; j++){
		num += arr[j];
		while(num >= s){
			subLen = j - i + 1;
			result = result > subLen ? subLen : result;
			num -= arr[i++];
		}
	}
	return result != INT_MAX ? result : 0;
}
int** generate(int n) {
	int **arr = (int **)malloc(sizeof(int *) * n);
	for (int i = 0; i < n; i++) {
		arr[i] = (int *)malloc(sizeof(int) * n);
	}
	return arr;
}

//螺旋矩阵II
int** generateMatrix(int n){
	int **result = generate(n);
	//声明需要执行几次
	int loop = n / 2;
	//声明中间元素位置，若n为奇数需要特殊处理
	int middle = n / 2;
	//声明开始的位置
	int startx = 0, starty = 0;
	int offest = 1;
	int count = 1;
	while (loop--) {
		int i = startx;
		int j = starty;
		//最上侧从左至右
		for (j; j < n - offest; j++) {
			result[i][j] = count++;
		}
		//最右侧从上到下
		for (i; i < n - offest; i++) {
			result[i][j] = count++;
		}
		//最下侧从右到左
		for (; j > startx; j--) {
			result[i][j] = count++;
		}
		//从最左侧从下到上
		for (; i > starty ; i--) {
			result[i][j] = count++;
		}
		startx += 1;
		starty += 1;
		offest += 1;
	}
	if (n % 2 == 1) {
		result[middle][middle] = count;
	}
	return result;
}

// int main(){
// //	int arr[2][2] = {
// //	1, 2,
// //	3, 4
// //	};
// //	printf(" %0x\n %0x\n %0x\n %0x\n",
// //	&arr[0][0], &arr[0][1], &arr[1][0],&arr[1][1]);
// 	int x = 5;
// 	int** result = generateMatrix(x);
// 	for (int i = 0; i < x; i++) {
// 		for (int j = 0; j < x; j++) {
// 			printf("%d ", result[i][j]);
// 		}
// 		printf("\n");
// 	}
// 	return 0;
// }


//区间长度问题
// int main() {
// 	int n;
// 	int a, b;
// 	scanf("%d", &n);
// 	int *arr = (int *)malloc(sizeof(int));
// 	int *pi = (int *)malloc(sizeof(int));
// 	for (int i = 0; i < n; i++) {
// 		scanf("%d", &arr[i]);
// 	}
// 	pi[0] = arr[0];
// 	for (int i = 1; i < n; i++) {
// 		pi[i] = pi[i - 1] + arr[i];
// 	}
// 	while (scanf("%d %d", &a, &b)) {
// 		if (a == 0)
// 			printf("%d\n",  pi[b]);
// 		else
// 			printf("%d\n", pi[b] - pi[a - 1]);
// 	}
// 	return 0;
// }
int min(int a, int b) {
	return a < b ? a : b;
}

int main() {
	int n, m;
	int num = 0;
	scanf("%d %d", &n, &m);
	int **arr = (int **)malloc(sizeof(int *) * n);

	for (int i = 0; i < n; i++) {
		arr[i] = (int *)malloc(sizeof(int) * m);
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &arr[i][j]);
			num += arr[i][j];
		}
	}

	printf("the all elements addition is %d\n", num);
	int h[n];
	int v[m];

	int hNum = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			hNum += arr[i][j];
		}
		h[i] = hNum;
	}

	int vNum = 0;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			vNum += arr[j][i];
		}
		v[i] = vNum;
	}

	int result = INT_MAX;
	for (int i = 0; i < n; i++) {
		result = min(result, abs(num - h[i] - h[i]));
	}

	for (int i = 0; i < m; i++) {
		result = min(result, abs(num - v[i] - v[i]));
	}
	printf("the min differ is %d", result);
	return 0;
}