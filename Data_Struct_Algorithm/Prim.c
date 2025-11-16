#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100
#define INF INT_MAX

/**
    @brief Prim算法求最小生成树,将点集分成两个集合
    @param graph 无向图的邻接矩
    @param vertices 顶点数
*/
void primMST(int graph[MAX_VERTICES][MAX_VERTICES], int vertices) {
    int parent[MAX_VERTICES];   // 储存最小生成树的父节点
    int key[MAX_VERTICES];      // 储存顶点的键值
    bool mstSet[MAX_VERTICES];  // 标记顶点是否在MST中

    // 初始化
    for (int i = 0; i < vertices; i++) {
        key[i] = INF;
        mstSet[i] = false;  // 没有顶点被添加到已知点集中
    }

    // 从第一个顶点开始
    key[0] = 0;
    parent[0] = -1;

    // 开始遍历，每一次添加一个节点，第一次循环只有根节点的key不为零，添加根节点，更新距离数组
    for (int count = 0; count < vertices - 1; count++) {
        int minKey = INF;
        int minIndex = -1;

        // 遍历原点集中的各点的最小边权值， 找出最小边权值的点，作为新加入的点
        for (int v = 0; v < vertices; v++) {
            if (!mstSet[v] && key[v] < minKey) {
                minKey = key[v];
                minIndex = v;
            }
        }

        mstSet[minIndex] = true;

        // 已经将新点添加到了最小树点集中， 现在用新点更新原点集中边的权重
        // 遍历所有顶点
        for (int v = 0; v < vertices; v++) {
            // 要满足：此顶点与新顶点有边；此顶点还不在最小树点集中
            // 在两点间的新带权边权值小于原权值时更新
            if (graph[minIndex][v] != 0 && !mstSet[v] &&
                graph[minIndex][v] < key[v]) {
                parent[v] = minIndex;         // 构建父子节点关系
                key[v] = graph[minIndex][v];  // 更新此顶点的最小边权值
            }
        }
    }
    printf("Prim算法生成的最小生成树边：\n");
    printf("边\t权重\n");
    int totalWeight = 0;
    for (int i = 1; i < vertices; i++) {
        printf("%d - %d\t%d\n", parent[i], i, graph[i][parent[i]]);
        totalWeight += graph[i][parent[i]];
    }
    printf("最小生成树总权重：%d\n", totalWeight);
}

int main() {
    int vertices, edges;
    printf("请输入顶点数：");
    scanf("%d", &vertices);

    int graph[MAX_VERTICES][MAX_VERTICES] = {0};

    printf("请输入边数：");
    scanf("%d", &edges);

    printf("请输入边和权重：\n");
    for (int i = 0; i < edges; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = w;
        graph[v][u] = w;  // 无向图邻接矩阵
    }

    primMST(graph, vertices);

    return 0;
}