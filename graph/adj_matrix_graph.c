#define DIF INT_MIN
#define EXPANSION_TIME 2
#include "../ds/queue.c"
#include <stdatomic.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
//使用邻接矩阵构造图：使用无向图
//使用1表示有边，0表示没有边
typedef struct GRAPH_ADJ_MATRIX {
    int capacity;
    //定义顶点和边的数量
    int numsV;
    int numsE;
    //顶点信息
    int *V;
    //边信息
    int **E;
}GRAPH_ADJ_MATRIX;

/**
 * @description 初始化邻接矩阵图
 * 最大容量为cap的两倍
 * 边权值为INT_MIN代表两结点之间不存在边
 * @param cap 初始化结点数量
 * @return 图
 */
GRAPH_ADJ_MATRIX *init_adj_matrix_graph(int cap);

/**
 * @description 向图中插入一条边并设置权值
 * @param graph 图
 * @param index_x 第x个结点
 * @param index_y 第y个结点
 * @param power_weight 权值
 */
void insert_e_adj_matrix_graph(GRAPH_ADJ_MATRIX *graph, int index_x, int index_y, int power_weight);

/**
 * @description 插入一个结点（按照递增插入）
 * @param graph 图
 */
void insert_v_adj_matrix_graph(GRAPH_ADJ_MATRIX *graph);

/**
 * @description 删除图中的一个结点
 * @param x 要删除的结点x
 * @param graph 图
 */
void delete_v_adj_matrix_graph(GRAPH_ADJ_MATRIX *graph, int x);

/**
 * @description 广度遍历图
 * @param graph 图
 * @param node_index 开始结点
 */
void bfs_traverse_adj_matrix_graph(GRAPH_ADJ_MATRIX *graph, int node_index);

/**
 * @description 对邻接矩阵图扩容
 * @param graph 图
 * @return 1为成功，0为失败
 */
int expansion_adj_matrix_graph(GRAPH_ADJ_MATRIX *graph);

/**
 * @description dfs邻接矩阵图
 * @param start_node 开始的结点
 * @param visited 访问数组
 * @param graph 图
 */
void dfs_adj_matrix_graph(GRAPH_ADJ_MATRIX *graph, bool *visited, int start_node);

/**
 * @description 深度遍历图
 * @param graph 图
 */
void dfs_traverse_adj_matrix_graph(GRAPH_ADJ_MATRIX *graph);

/**
 * @description 打印邻接矩阵图的信息
 * @param graph 图
 */
void printf_adj_matrix_graph(GRAPH_ADJ_MATRIX *graph);

/**
 * @description 销毁邻接矩阵图
 * @param graph 图
 */
void destroy_adj_matrix_graph(GRAPH_ADJ_MATRIX *graph);

/**
 * @description 获取v中val的索引值
 * @param v v数组
 * @param val 值
 * @param len v的长度
 * @return val对应的index
 */
int get_v_index_adj_matrix_graph_v(int *v, int val, int len);

GRAPH_ADJ_MATRIX *init_adj_matrix_graph(int cap) {
    GRAPH_ADJ_MATRIX *graph = (GRAPH_ADJ_MATRIX *)malloc(sizeof(GRAPH_ADJ_MATRIX));
    graph->numsE = 0;
    //容量设置为初始化的2倍
    graph->capacity = EXPANSION_TIME * cap;
    graph->numsV = cap;
    //初始化存储结点和边的空间
    graph->V = (int *)malloc(sizeof(int) * graph->capacity);
    graph->E = (int **)malloc(sizeof(int *) * graph->capacity);
    for (int i = 0; i < graph->capacity; i++) {
        graph->E[i] = (int *)malloc(sizeof(int) * graph->capacity);
    }
    //初始化结点值和结点之间的边
    for (int i = 0; i < graph->numsV; i++) {
        //初始化结点值
        graph->V[i] = i;
        for (int j = 0; j < graph->numsV; j++) {
            graph->E[i][j] = DIF;
        }
    }
    return graph;
}

void insert_e_adj_matrix_graph(GRAPH_ADJ_MATRIX *graph, int x, int y, int power_weight) {
    int index_x = get_v_index_adj_matrix_graph_v(graph->V, x, graph->numsV);
    int index_y = get_v_index_adj_matrix_graph_v(graph->V, y, graph->numsV);
    if (index_x < 0 || index_y < 0) {
        printf("the param has error!\n");
        return ;
    }
    graph->E[index_x][index_y] = power_weight;
    graph->E[index_y][index_x] = power_weight;
    graph->numsE++;
}

int expansion_adj_matrix_graph(GRAPH_ADJ_MATRIX *graph) {
    int new_capacity = graph->capacity * EXPANSION_TIME;
    int * new_v = realloc(graph->V, sizeof(int) * new_capacity);
    if (new_v == NULL) {
        return 0;
    }
    graph->V = new_v;
    int **new_e = realloc(graph->E, sizeof(int *) * new_capacity);
    if (new_e == NULL) {
        return 0;
    }
    graph->E = new_e;
    for (int i = 0; i < new_capacity; i++) {
        int *new_e_i = (int *)malloc(sizeof(int) * new_capacity);
        if (new_e_i == NULL) {
            for (int j = 0; j < i; j++) {
                free(graph->E[j]);
            }
            return 0;
        }
        graph->E[i] = new_e_i;
    }
    return 1;
}

void dfs_adj_matrix_graph(GRAPH_ADJ_MATRIX *graph, bool *visited, int start_node) {
    printf("%d ", start_node);
    visited[start_node] = true;
    for (int i = 0; i < graph->numsV; i++) {
        if (graph->E[start_node][i] != DIF && !visited[i]) {
            dfs_adj_matrix_graph(graph, visited, i);
        }
    }
}

void dfs_traverse_adj_matrix_graph(GRAPH_ADJ_MATRIX *graph) {
    bool visited[graph->numsV];
    for (int i = 0; i < graph->numsV; i++) {
        visited[i] = false;
    }
    for (int i = 0; i < graph->numsV; i++) {
        if (!visited[i]) {
            dfs_adj_matrix_graph(graph, visited, i);
        }
    }
    printf("\n");
}

void insert_v_adj_matrix_graph(GRAPH_ADJ_MATRIX *graph) {
    //如果结点数量大于最大容量了
    if (graph->numsV + 1 > graph->capacity) {
        if (!expansion_adj_matrix_graph(graph)) {
            return ;
        }
    }
    //获取到最大的节点值
    int max_node = graph->V[graph->numsV - 1];
    graph->V[graph->numsV] = max_node + 1;
    //处理边
    for (int i = 0; i < graph->numsV + 1; i++) {
        if (i < graph->numsV) {
            graph->E[i][graph->numsV] = DIF;
        }
        graph->E[graph->numsV][i] = DIF;
    }
    graph->numsV++;
}

int get_v_index_adj_matrix_graph_v(int *v, int val, int len) {
    int result = -1;
    for (int i = 0; i < len; i++) {
        if (v[i] == val) {
            result = i;
            break;
        }
    }
    return result;
}

void delete_v_adj_matrix_graph(GRAPH_ADJ_MATRIX *graph, int x) {
    int index_x = get_v_index_adj_matrix_graph_v(graph->V, x, graph->numsV);
    if (index_x < 0 || graph->numsV == 0) {
        return;
    }
    //统计要删除的结点上有几条边
    int e = 0;
    for (int i = 0; i < graph->numsV; i++) {
        if (graph->E[index_x][i] != DIF) {
            e++;
        }
    }
    //移动v中的数据
    for (int i = index_x; i < graph->numsV - 1; i++) {
        graph->V[i] = graph->V[i + 1];
    }
    //移动e中的数据
    for (int i = index_x; i < graph->numsV - 1; i++) {
        for (int j = 0; j < graph->numsV; j++) {
            graph->E[j][i] = graph->E[j][i + 1];
        }
    }
    for (int i = index_x; i < graph->numsV - 1; i++) {
        for (int j = 0; j < graph->numsV; j++) {
            graph->E[i][j] = graph->E[i + 1][j];
        }
    }
    //改变图的信息
    graph->numsV--;
    graph->numsE = graph->numsE - e;
}

void bfs_traverse_adj_matrix_graph(GRAPH_ADJ_MATRIX *graph, int node_index) {
    Queue * queue = init_queue();
    bool visited[graph->numsV];
    for (int i = 0; i < graph->numsV; i++) {
        visited[i] = false;
    }
    in_queue(queue, node_index);
    visited[node_index] = true;
    while (queue->rear != queue->front) {
        int out_val = out_queue(queue);
        printf("%d ", out_val);
        for (int i = 0; i < graph->numsV; i++) {
            if (graph->E[out_val][i] != DIF && !visited[i]) {
                in_queue(queue, i);
                visited[i] = true;
            }
        }
    }
}

void printf_adj_matrix_graph(GRAPH_ADJ_MATRIX *graph) {
    //打印节点信息
    printf("the adj_matrix_graph has number %d points, v are: \n", graph->numsV);
    for (int i = 0; i < graph->numsV; i++) {
        printf("%d ", graph->V[i]);
    }
    printf("\n");
    printf("the adj_matrix_graph's e are: \n");
    for (int i = 0; i < graph->numsV; i++) {
        for (int j = 0; j < graph->numsV; j++) {
            //如果一条边是有意义的，则进行输出权值和对应的结点
            if (graph->E[i][j] != DIF) {
                printf("%d --- %d : the power-weight is %d\n", graph->V[i], graph->V[j], graph->E[i][j]);
            }
        }
    }
    printf("\n");
}

void destroy_adj_matrix_graph(GRAPH_ADJ_MATRIX *graph) {
    if (graph == NULL) {
        return;
    }
    for (int i = 0; i < graph->capacity; i++) {
        free(graph->E[i]);
    }
    free(graph->E);
    free(graph->V);
    free(graph);
}

void printf_info_adj_matrix_graph(char *s) {
    printf("================================== %s ==================================\n", s);
}
int main(){
    // GRAPH_ADJ_MATRIX * graph_adj_matrix = init_adj_matrix_graph(4);
    // insert_e_adj_matrix_graph(graph_adj_matrix, 0, 1, 4);
    // insert_e_adj_matrix_graph(graph_adj_matrix, 0, 2, 7);
    // insert_e_adj_matrix_graph(graph_adj_matrix, 3, 2, 2);
    // printf_adj_matrix_graph(graph_adj_matrix);
    // insert_v_adj_matrix_graph(graph_adj_matrix);
    // printf_info_adj_matrix_graph("after insert a node in the graph!");
    // printf_adj_matrix_graph(graph_adj_matrix);
    // delete_v_adj_matrix_graph(graph_adj_matrix, 0);
    // printf_info_adj_matrix_graph("after delete 0 node in the graph!");
    // printf_adj_matrix_graph(graph_adj_matrix);
    // destroy_adj_matrix_graph(graph_adj_matrix);
    // GRAPH_ADJ_MATRIX * graph_adj_matrix = init_adj_matrix_graph(5);
    // insert_e_adj_matrix_graph(graph_adj_matrix, 0, 3, 2);
    // insert_e_adj_matrix_graph(graph_adj_matrix, 2, 1, 5);
    // insert_e_adj_matrix_graph(graph_adj_matrix, 1, 4, 9);
    // insert_e_adj_matrix_graph(graph_adj_matrix, 3, 4, 1);
    // insert_e_adj_matrix_graph(graph_adj_matrix, 0, 2, 8);
    // printf_info_adj_matrix_graph("the adj_matrix_graph info!");
    // printf_adj_matrix_graph(graph_adj_matrix);
    // printf_info_adj_matrix_graph("dfs the adj_matrix_graph!");
    // dfs_traverse_adj_matrix_graph(graph_adj_matrix);
    // printf_info_adj_matrix_graph("bfs the adj_matrix_graph!");
    // bfs_traverse_adj_matrix_graph(graph_adj_matrix, 0);
    return 0;
}
