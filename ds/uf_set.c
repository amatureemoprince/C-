#define MAX_SIZE 4
#include <iso646.h>
#include <stdio.h>
#include <stdlib.h>

//自身索引就为结点编号
//     0   1   2
//    -1  -1  -1
typedef struct UF_SET {
    int uf_set[MAX_SIZE];
}UF_SET;

void init_uf_set(UF_SET *set) {
    for (int i = 0; i < MAX_SIZE; i++) {
        set->uf_set[i] = -1;
    }
}

int uf_set_find(UF_SET *uf_set, int val) {
    while (uf_set->uf_set[val] >= 0) {
        val = uf_set->uf_set[val];
    }
    return val;
}

//对find进行优化，若查找的x元素不在树的第二层，直接令其为第二层！
int uf_set_find_better(UF_SET *uf_set, int x) {
    int root = x;
    //先找到root结点
    while (root >= 0) {
        root = uf_set->uf_set[root];
    }
    //找到root结点了，压缩路径
    //如果是有父结点，则进行设置
    while (root != x) {
        int temp = uf_set->uf_set[x];
        uf_set->uf_set[x] = root;
        x = temp;
    }
    return root;
}

void uf_set_union(UF_SET *uf_set, int x, int y) {
    // int root_x = uf_set_find(uf_set, x);
    // int root_y = uf_set_find(uf_set, y);
    int root_x = uf_set_find_better(uf_set, x);
    int root_y = uf_set_find_better(uf_set, y);
    if (root_x == root_y)
        return;
    uf_set->uf_set[root_x] = uf_set->uf_set[root_x] + uf_set->uf_set[root_y];
    uf_set->uf_set[root_y] = root_x;
}

void print_uf_set(UF_SET *uf_set) {
    for (int i = 0; i < MAX_SIZE; i++) {
        printf(" %d ", i);
    }
    printf("\n");
    for (int i = 0; i < MAX_SIZE; i++) {
        printf("%d ", uf_set->uf_set[i]);
    }
    printf("\n");
    printf("\n");
}

int main(){
    UF_SET * uf_set = (UF_SET *)malloc(sizeof(UF_SET));
    init_uf_set(uf_set);
    printf(" %d\n", uf_set_find(uf_set, 3));
    print_uf_set(uf_set);
    // uf_set_union(uf_set, 2, 3);
    // uf_set_union(uf_set, 6, 7);
    uf_set_union(uf_set, 0, 1);
    print_uf_set(uf_set);
    // print_uf_set(uf_set);
    // uf_set_union(uf_set, 7, 2);
    uf_set_union(uf_set, 2, 3);
    print_uf_set(uf_set);
    uf_set_union(uf_set, 1, 3);
    print_uf_set(uf_set);
}