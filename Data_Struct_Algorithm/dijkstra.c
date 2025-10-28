#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct Graph {
    int vertices;  // 顶点数
    int** matrix;  // 邻接矩阵
} Graph;

// 创建图
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->vertices = vertices;
    graph->matrix = (int**)malloc(sizeof(Graph));
    // 邻接矩阵中除了自身到自身，剩下的距离初始化为inf
    for (int i = 0; i < vertices; i++) {
        graph->matrix[i] = (int*)malloc(vertices * sizeof(int*));
        for (int j = 0; j < vertices; j++) {
            graph->matrix[i][j] = (i == j) ? 0 : INT_MAX;
        }
    }
    return graph;
}

// 添加边
void addEdge(Graph* graph, int src, int dest, int weight) {
    // 对起点和终点的越界检查
    if (src >= 0 && src < graph->vertices && dest >= 0 &&
        dest < graph->vertices) {
        graph->matrix[src][dest] = weight;
        graph->matrix[dest][src] = weight;
    }
}

// 寻找最小距离
int minDistance(int dist[], bool processed[], int vertices) {
    int min = INT_MAX, min_index = -1;
    for (int v = 0; v < vertices; v++) {
        if (!processed[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// 打印最短路径
void printSolution(int dist[], int vertices, int src) {
    printf("顶点\t从顶点%d出发的最短距离\n", src);
    for (int i = 0; i < vertices; i++) {
        if (dist[i] == INT_MAX) {
            printf("%d\t不可达\n", i);
        } else {
            printf("%d\t%d\n", i, dist[i]);
        }
    }
}

// 打印完整路径
void printPath(int parent[], int j) {
    // 基础情况：如果是源顶点
    if (parent[j] == -1) {
        printf("%d", j);
        return;
    }

    printPath(parent, parent[j]);
    printf(" -> %d", j);
}

// 打印所有路径
void printAllPaths(int dist[], int parent[], int vertices, int src) {
    printf("\n从顶点%d到各顶点的最短路径:\n", src);
    for (int i = 0; i < vertices; i++) {
        if (i != src) {
            if (dist[i] == INT_MAX) {
                printf("%d 到 %d: 不可达\n", src, i);
            } else {
                printf("%d 到 %d: 距离=%d, 路径=", src, i, dist[i]);
                printPath(parent, i);
                printf("\n");
            }
        }
    }
}

void dijkstra(Graph* graph, int src) {
    int vertices = graph->vertices;
    int dist[vertices];        // 存储从原点到每个顶点的最短距离
    bool processed[vertices];  // 标记顶点是否已经处理
    int parent[vertices];

    // 初始化
    for (int i = 0; i < vertices; i++) {
        dist[i] = INT_MAX;
        processed[i] = false;
        parent[i] = -1;
    }

    // 原点到自身的距离为0
    dist[src] = 0;

    // 找到所有顶点的最短路径，每次遍历加入一个节点，循环节点数-1
    for (int count = 0; count < vertices - 1; count++) {
        // 选择为处理顶点中的距离最小的顶点
        int u = minDistance(dist, processed, vertices);
        // 如果没有任何一个顶点可达，那就不是连通图，提前结束
        if (u == -1) break;
        // 标记当前顶点为已处理
        processed[u] = true;
        // 更新u的所有临接节点的距离
        for (int v = 0; v < vertices; v++) {
            // 如果：v未被处理；u到v有边；通过u到v的路径比当前记录的更短
            if (!processed[v] && graph->matrix[u][v] != INT_MAX &&
                dist[u] != INT_MAX && dist[u] + graph->matrix[u][v] < dist[v]) {
                dist[v] = dist[v] + graph->matrix[u][v];
                parent[v] = u;
            }
        }
    }
    printSolution(dist, vertices, src);
    printAllPaths(dist, parent, vertices, src);
}

void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->vertices; i++) {
        free(graph->matrix[i]);
    }
    free(graph->matrix);
    free(graph);
}

// 测试函数
int main() {
    int vertices, edges;

    printf("输入顶点数: ");
    scanf("%d", &vertices);

    Graph* graph = createGraph(vertices);

    printf("输入边数: ");
    scanf("%d", &edges);

    printf("输入边和权重 (格式: 源点 目标点 权重):\n");
    for (int i = 0; i < edges; i++) {
        int src, dest, weight;
        scanf("%d %d %d", &src, &dest, &weight);
        addEdge(graph, src, dest, weight);
    }

    int source;
    printf("输入源点: ");
    scanf("%d", &source);

    dijkstra(graph, source);

    freeGraph(graph);
    return 0;
}
