#include "limits.h"
#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"

#define MAX_VERTICES 100
#define INF INT_MAX

void floydWarshall(int graph[][MAX_VERTICES], int vertices) {
    int dist[MAX_VERTICES][MAX_VERTICES];  // 最短距离矩阵
    int next[MAX_VERTICES][MAX_VERTICES];  // 路径重建矩阵

    // 初始化距离矩阵和路径矩阵
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            dist[i][j] = graph[i][j];
            if (graph[i][j] != INF && i != j) {
                next[i][j] = j;
            } else {
                next[i][j] = -1;
            }
        }
    }

    // 佛洛依德算法核心
    for (int k = 0; k < vertices; k++) {
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }
}

// 图初始化
void initializeGraph(int graph[][MAX_VERTICES], int vertices) {
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (i == j) {
                graph[i][j] = 0;  // 顶点到自身的距离为0
            } else {
                graph[i][j] = INF;
            }
        }
    }
}