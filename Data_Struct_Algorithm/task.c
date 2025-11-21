#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"

typedef struct Graph {
    int vertices;
    int** adjMatrix;
    int* degrees;
    bool* visited;
} Graph;

Graph* createGraph(int n) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->adjMatrix = (int**)malloc(sizeof(int) * n * n);
    graph->degrees = (int*)malloc(sizeof(int) * n);
    graph->visited = (bool*)malloc(sizeof(bool) * n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph->adjMatrix[i][j] = 0;
        }
        graph->visited[i] = false;
    }
}

void addEdge(Graph* graph, int src, int dest) {
    src--;
    dest--;
    graph->adjMatrix[src][dest] = 1;
    graph->adjMatrix[dest][src] = 1;
    graph->degrees[src]++;
    graph->degrees[dest]++;
}

bool isDoubleDegrees(Graph* graph) {
    for (int i = 0; i < graph->vertices; i++) {
        if (graph->degrees[i] % 2 != 0) {
            return false;
        }
    }
    return true;
}

void DFS(Graph* graph, int current) {
    graph->visited[current] = true;

    for (int i = 0; i < graph->vertices; i++) {
        if (graph->adjMatrix[current][i] == 1) {
            DFS(graph, i);
        }
    }
}

bool isEular(Graph* graph) {
    for (int i = 0; i < graph->vertices; i++) {
        if (graph->visited[i] == false) {
            return false;
        }
    }
    return true;
}

typedef struct TreeNode {
    int val
};