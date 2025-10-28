#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100
#define MAX_EDGES 1000;

// 定义边结构体：起点，终点，权重
typedef struct Edge {
    int src, dest, weight;
} Edge;

// 定义图结构体
typedef struct Graph {
    int V, E;     // 顶点数，边数
    Edge* edges;  // 边数组
} Graph;

// 查并集结构
typedef struct Subset {
    int parent;
    int rank;
} Subset;

// 创建图
Graph* createGraph(int V, int E) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->E = E;
    graph->edges = (Edge*)malloc(sizeof(Edge));
    return graph;
}

int find(Subset subsets[], int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

// 按秩合并
void Union(Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    // 按秩合并
    if (subsets[xroot].rank < subsets[yroot].rank) {
        subsets[xroot].parent = yroot;
    } else if (subsets[xroot].rank > subsets[yroot].rank) {
        subsets[yroot].parent = xroot;
    } else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// 比较函数，用于排序
int compareEdges(const void* a, const void* b) {
    Edge* edge1 = (Edge*)a;
    Edge* edge2 = (Edge*)b;
    return edge1->weight - edge2->weight;
}

void kruskalMST(Graph* graph) {
    int V = graph->V;
    Edge result[V];  // 储存MST结果
    int e = 0;       // 用于储存result数组的索引
    int i = 0;       // 用于排序边的索引

    // 第一步：按权重排列所有边
    qsort(graph->edges, graph->E, sizeof(graph->edges[0]), compareEdges);
    // 为并查集分配内存
    Subset* subsets = (Subset*)malloc(V * sizeof(Subset));
    // 初始化并查集
    for (int v = 0; v < V; V++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
    // MST的边数为V-1
    while (e < V - 1 && i < graph->E) {
        Edge next_edge = graph->edges[i++];
        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }
}