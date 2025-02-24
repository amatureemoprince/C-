#define DEFAULT_SIZE 10
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//声明动态数据类型
typedef struct Dynamic {
  int *data;
  int max_size;
  int size;
}Dynamic;

Dynamic *init() {
  Dynamic *dynamic = (Dynamic *)malloc(sizeof(Dynamic));
  if (dynamic == NULL) {
    fprintf(stderr, "memory allocation fails");
    return NULL;
  }
  dynamic->size = 0;
  dynamic->max_size = DEFAULT_SIZE;
  dynamic->data = (int *) malloc(sizeof(int) * dynamic->max_size);
  if (dynamic->data == NULL) {
    fprintf(stderr, "dynamic->data memory allocation fails");
    return NULL;
  }
  //如果使用malloc分配内存是不会初始化的而且可能包含垃圾值
  //int *data = (int *) calloc(dynamic->max_size, sizeof(int));
  //使用calloc就可以在初始化时就赋值
  memset(dynamic->data, 0, dynamic->max_size * sizeof(int));
  return dynamic;
}

/**
 * 尾部插入元素
 * @param dynamic 动态数组
 * @param data 插入的元素
 */
void insert_auto_extension(Dynamic *dynamic, const int data) {
  if (dynamic == NULL) {
    fprintf(stderr, "dynamic is the NULL");
    return;
  }
  if (dynamic->size < dynamic->max_size) {
    dynamic->data[dynamic->size++] = data;
    return;
  }
  const int new_max_size = dynamic->max_size + dynamic->max_size / 2;
  //realloc分配成功会复制之前的数组数组
  int *new_data = (int *)realloc(dynamic->data, new_max_size * sizeof(int));
  if (new_data == NULL) {
    fprintf(stderr, "Memory reallocation failed\n");
    return;
  }
  dynamic->data = new_data;
  dynamic->max_size = new_max_size;
  dynamic->data[dynamic->size++] = data;
}

/**
 *
 * @param dynamic 动态数组
 * @param index 删除元素的索引
 */
void delete(Dynamic *dynamic, const int index){
  if (dynamic == NULL) {
    fprintf(stderr, "dynamic is the NULL");
    return;
  }
  if (dynamic->size == 0) {
    printf("the dynamic array's size is 0, you can't delete element in it");
    return;
  }
  if (index >= dynamic->size) {
    printf("don't have %d elements", index);
    return;
  }
  for (int i = index; i < dynamic->size - 1; i++) {
    dynamic->data[i] = dynamic->data[i + 1];
  }
  dynamic->size--;
}


void mine_printf(const Dynamic dynamic) {
  printf("dynamic's max_size is %d\n", dynamic.max_size);
  printf("dynamic's size is %d\n", dynamic.size);
  printf("dynamic's data are : [");
  for (int i = 0; i < dynamic.size; i++) {
    printf("%d", dynamic.data[i]);
    if (i < dynamic.size - 1) {
      printf(", ");
    }
  }
  printf("]\n");
}
int main(void){
  // TODO: 测试初始化
  Dynamic * dynamic = init();
  mine_printf(*dynamic);
  // TODO: 测试插入
  printf("insert:------------------\n ");
  for (int i = 0; i < 12; i++) {
    insert_auto_extension(dynamic,  i);
  }
  mine_printf(*dynamic);
  // TODO: 测试删除
  delete(dynamic, 3);
  printf("delete:------------------\n");
  mine_printf(*dynamic);
  free(dynamic);
  return 0;
}
