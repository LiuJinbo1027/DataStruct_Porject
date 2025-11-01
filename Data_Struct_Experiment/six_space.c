#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_IN 104

typedef struct Node {
    int vertex;  // 顶点
    struct Node* next;
} Node;

// 定义队列结构
typedef struct {
    int items[MAX_IN];
    int front;  // 队列头
    int rear;   // 队列尾
} Queue;

// 队列初始化
void initQueue(Queue* q) {
    q->front = -1;
    q->rear = -1;
}

bool isEmpty(Queue* q) { return q->front == -1; }

// 元素入队操作
void enqueue(Queue* q, int value) {
    if (q->rear == MAX_IN - 1) {
        return;  // 队列已满
    }
    // 处理第一个元素
    if (q->front == -1) {
        q->front = 0;
    }
    q->rear++;
    q->items[q->rear] = value;  // 把新元素放在队列尾，尾顺延一位
}

// 元素出队操作
int dequeue(Queue* q) {
    if (isEmpty(q)) {
        return -1;
    }

    int item = q->items[q->front];  // 找到队头元素
    q->front++;                     // 队头前进一位
    if (q->front > q->rear) {
        q->front = q->rear = -1;  // 如果队被清空了，重制标志位
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
// 注意：这个链表的方向时是“往回指”的： 边链表<- 节点a<- 节点b ...
void addEdge(Node* adj[], int src, int dest) {
    Node* newNode = createNode(dest);  // 创建终点节点
    newNode->next = adj[src];          // 边链表标志位 <- 新节点
    adj[src] = newNode;                // 把标志位放在新节点上
    // 由于是无向图，反过来同理操作
    newNode = createNode(src);
    newNode->next = adj[dest];
    adj[dest] = newNode;
}

int BFS(Node* adj[], int start, int n, bool visited[]) {
    Queue q;
    initQueue(&q);

    int level[MAX_IN] = {0};  // 初始距离为0
    int count = 1;

    // 初始化访问数组
    for (int i = 1; i <= n; i++) {
        visited[i] = false;
    }

    visited[start] = true;
    level[start] = 0;
    enqueue(&q, start);

    while (!isEmpty(&q)) {          // 只要队列不空
        int current = dequeue(&q);  // 队头节点出队

        Node* temp = adj[current];  // 取队列头节点的表链表节点
        while (temp != NULL) {
            int neighbour = temp->vertex;

            if (!visited[neighbour]) {  // 如果节点没有被遍历过
                visited[neighbour] = true;
                // 计算此节点到进行六度判断的节点的距离
                level[neighbour] = level[current] + 1;

                if (level[neighbour] <= 6) {  // 满足六度距离内
                    count++;
                    // 此节点也入队，在此基础上继续找他的表链表节点
                    enqueue(&q, neighbour);
                }
            }
            temp = temp->next;  // 遍历边链表下的节点
        }
    }
    return count;
}
int main() {
    int n, m;  // 顶点数，边数
    scanf("%d %d", &n, &m);

    Node* adj[MAX_IN] = {NULL};  // 定义边链表

    // 获得所有边
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(adj, u, v);
    }

    bool visited[MAX_IN];

    // 对每个节点都用BFS广度搜索，找到所有符合条件的点
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