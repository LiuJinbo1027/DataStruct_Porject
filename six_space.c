#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_IN 104

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// 定义队列结构
typedef struct {
    int items[MAX_IN];
    int front;
    int rear;
} Queue;

// 队列初始化
void initQueue(Queue* q) {
    q->front = -1;
    q->rear = -1;
}

bool isEmpty(Queue* q) { return q->front == -1; }

void enqueue(Queue* q, int value) {
    if (q->rear == MAX_IN - 1) {
        return;  // 队列已满
    }

    if (q->front == -1) {
        q->front = 0;
    }
    q->rear++;
    q->items[q->rear] = value;
}

int dequeue(Queue* q) {
    if (isEmpty(q)) {
        return -1;
    }

    int item = q->items[q->front];
    q->front++;
    if (q->front > q->rear) {
        q->front = q->rear = -1;
    }
    return item;
}

Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// 添加边到邻接表
void addEdge(Node* adj[], int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = adj[src];
    adj[src] = newNode;

    newNode = createNode(src);
    newNode->next = adj[dest];
    adj[dest] = newNode;
}

int BFS(Node* adj[], int start, int n, bool visited[]) {
    Queue q;
    initQueue(&q);

    int level[MAX_IN] = {0};
    int count = 1;

    // 初始化访问数组
    for (int i = 1; i <= n; i++) {
        visited[i] = false;
    }

    visited[start] = true;
    level[start] = 0;
    enqueue(&q, start);

    while (!isEmpty(&q)) {
        int current = dequeue(&q);

        Node* temp = adj[current];
        while (temp != NULL) {
            int neighbour = temp->vertex;

            if (!visited[neighbour]) {
                visited[neighbour] = true;
                level[neighbour] = level[current] + 1;

                if (level[neighbour] <= 6) {
                    count++;
                    enqueue(&q, neighbour);
                }
            }
            temp = temp->next;
        }
    }
    return count;
}
int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    Node* adj[MAX_IN] = {NULL};

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(adj, u, v);
    }

    bool visited[MAX_IN];

    for (int i = 1; i <= n; i++) {
        int count = BFS(adj, i, n, visited);
        double percentage = ((double)count / n) * 100;
        printf("%d:%.2lf%%\n", i, percentage);
    }

    // 释放邻接表内存
    for (int i = 1; i <= n; i++) {
        Node* temp = adj[i];
        while (temp != NULL) {
            Node* toDelete = temp;
            temp = temp->next;
            free(toDelete);
        }
    }

    return 0;
}