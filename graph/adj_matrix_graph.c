#define MAX_ADJ_V 100
#include <stdlib.h>
//使用邻接矩阵构造图：使用无向图
//使用1表示有边，0表示没有边
typedef struct GRAPH_ADJ_MATRIX {
    //当前容量
    int cap;
    //定义顶点和边的数量
    int numsV;
    int numsE;
    //顶点信息
    int *V;
    //边信息
    int **E;
}GRAPH_ADJ_MATRIX;


int adj_matrix_expansion(GRAPH_ADJ_MATRIX *graph);

int have_e_adj_matrix(GRAPH_ADJ_MATRIX *graph, int x, int y);

int insert_adj_matrix_v(GRAPH_ADJ_MATRIX *graph, int val);

GRAPH_ADJ_MATRIX *init_graph_adj_matrix(int initNum);

//初始图
//边数开始为0，每个结点初始化为i+1，数量为numV，numV为传入的要初始化的initNum。
//分配的内存要为cap，初始化的结点数可能小于cap
GRAPH_ADJ_MATRIX *init_graph_adj_matrix(int initNum) {
    GRAPH_ADJ_MATRIX *graph = (GRAPH_ADJ_MATRIX *)malloc(sizeof(GRAPH_ADJ_MATRIX));
    graph->numsE = 0;
    graph->numsV = initNum;
    graph->cap = (initNum > MAX_ADJ_V) ? initNum : MAX_ADJ_V;
    graph->V = (int *)malloc(sizeof(int) * graph->cap);
    graph->E = (int **)malloc(sizeof(int *) * graph->cap);
    for (int i = 0; i < graph->cap; i++) {
        graph->E[i] = (int *)malloc(sizeof(int) * graph->cap);
    }
    //初始化所有顶点值
    for (int i = 0; i < graph->numsV; i++) {
        graph->V[i] = i;
    }
    //初始化所有顶点之间没有边
    for (int i = 0; i < graph->numsV; i++) {
        for (int j = 0; j < graph->numsV; j++) {
            graph->E[i][j] = 0;
        }
    }
    return graph;
}


/**
 * @description 判断两个结点之间是否存在边
 *
 * @param graph 邻接图
 * @param x 索引为x的结点
 * @param y 索引为y的结点
 * @return 1为存在边，0为不存在边
 */
int have_e_adj_matrix(GRAPH_ADJ_MATRIX *graph, int x, int y) {
    return graph->E[x][y] == 1 ? 1 : 0;
}


/**
 * @description 邻接矩阵图扩容操作
 * @param graph 图
 * @return 1为扩容成功，0为扩容失败
 */
int adj_matrix_expansion(GRAPH_ADJ_MATRIX *graph) {
    int new_cap = graph->cap * 2;
    int *new_V = (int *)realloc(graph->V, sizeof(int) * new_cap);
    if (new_V == NULL) {
        return 0;
    }
    graph->V = new_V;
    int **new_E = (int **)realloc(graph->E, sizeof(int*) * new_cap);
    if (new_E == NULL) {
        return 0;
    }
    graph->E = new_E;
    for (int i = 0; i < new_cap; i++) {
        int *new_E_i = (int *)malloc(sizeof(int) * new_cap);
        if (new_E_i == NULL) {
            for (int j = 0; j < i; j++) {
                free(graph->E[j]);
            }
            return 0;
        }
        graph->E[i] = new_E_i;
    }
    return 1;
}

/**
 * @description 邻接矩阵图插入新的结点
 * @param graph 图
 * @param val 结点值
 * @return int 1为成功插入，0为失败插入
 */
int insert_adj_matrix_v(GRAPH_ADJ_MATRIX *graph, int val) {
    if (graph->numsV + 1 > graph->cap) {
        if (!adj_matrix_expansion(graph)) {
            return 0;
        }
    }
    graph->V[graph->numsV] = val;
    graph->numsV++;
    return 1;
}
/**
 * @description 邻接矩阵图添加一条边
 * @param graph 图
 * @param x 索引为x的结点
 * @param y 索引为y的结点
 * @return 1为添加边成功，0则失败
 */
int add_adj_matrix_e(GRAPH_ADJ_MATRIX *graph, int x, int y) {
    if (x > graph->cap || x < 0 || y > graph->cap || graph < 0) {
        return 0;
    }
    graph->E[x][y] = 1;
    graph->E[y][x] = 1;
    graph->numsE++;
    return 1;
}

/**
 * @description 获取邻接矩阵表索引为v的结点的相邻结点索引数组
 * @param graph 图
 * @param v 索引为v的结点
 * @param len 返回结果数组长度
 * @return 与之有边的顶点索引值
 */
int *get_e_by_v_adj_matrix(GRAPH_ADJ_MATRIX *graph, int v, int *len) {
    int *result = (int *)malloc(sizeof(int) * graph->cap);
    int resultIndex = 0;
    //遍历一行或者一列则可
    for (int i = 0; i < graph->numsV; i++) {
        if (graph->E[v][i] == 1) {
            result[resultIndex++] = i;
        }
    }
    (*len) = resultIndex;
    return result;
}
/**
 * @description 销毁邻接矩阵图
 * @param graph 图
 */
void destroy_adj_matrix(GRAPH_ADJ_MATRIX *graph) {
    if (graph == NULL) {
        return;
    }
    for (int i = 0; i < graph->numsV; i++) {
        free(graph->E[i]);
    }
    free(graph->E);
    free(graph->V);
    free(graph);
}
int main(){
    return 0;
}