#include <sys/types.h>

#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct QueueNode {
    TreeNode* treeNode;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
    int size;
} Queue;

typedef struct StackNode {
    TreeNode* treeNode;
    struct StackNode* next;
} StackNode;

typedef struct Stack {
    StackNode* top;
    int size;
} Stack;

void initQueue(Queue* q) {
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
}

bool isQueueEmpty(Queue* q) { return q->size == 0; }

void enqueue(Queue* q, TreeNode* treeNode) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->treeNode = treeNode;
    newNode->next = NULL;

    if (isQueueEmpty(q)) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->size++;
}

TreeNode* dequeue(Queue* q) {
    if (isQueueEmpty(q)) {
        return NULL;
    }

    QueueNode* temp = q->front;
    TreeNode* treeNode = temp->treeNode;

    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
    q->size--;
    return treeNode;
}

void initStack(Stack* s) {
    s->top = NULL;
    s->size = 0;
}

bool isStackEmpty(Stack* s) { return s->size == 0; }

void push(Stack* s, TreeNode* treeNode) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->treeNode = treeNode;
    newNode->next = s->top;
    s->top = newNode;
    s->size++;
}

TreeNode* pop(Stack* s) {
    if (isStackEmpty(s)) {
        return NULL;
    } else {
        StackNode* temp = s->top;
        TreeNode* treeNode = temp->treeNode;
        s->top = s->top->next;
        free(temp);
        s->size--;
        return treeNode;
    }
}

TreeNode* peek(Stack* s) {
    if (isQueueEmpty(s)) {
        return NULL;
    }
    return s->top->treeNode;
}

TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

TreeNode* buildSampleTree() {
    TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->right = createNode(6);
    root->left->left->left = createNode(7);
    return root;
}
void bfsTraversal(TreeNode* root) {
    if (root == NULL) return;

    Queue q;
    initQueue(&q);
    enqueue(&q, root);

    printf("BFS遍历");

    while (isQueueEmpty(&q)) {
        TreeNode* current = dequeue(&q);
        printf("%d", current->data);

        if (current->left != NULL) {
            enqueue(&q, current->left);
        }
        if (current->right != NULL) {
            enqueue(&q, current->right);
        }
    }
    printf("\n");
}

void dfsPreOrderRecursive(TreeNode* root) {
    if (root == NULL) return;

    printf("%d", root->data);
    dfsPreOrderRecursive(root->left);
    dfsPreOrderRecursive(root->right);
}

// DFS递归中序遍历
void dfsInOrderRecursive(TreeNode* root) {
    if (root == NULL) return;

    dfsInOrderRecursive(root->left);   // 遍历左子树
    printf("%d ", root->data);         // 访问根节点
    dfsInOrderRecursive(root->right);  // 遍历右子树
}

// DFS递归后序遍历
void dfsPostOrderRecursive(TreeNode* root) {
    if (root == NULL) return;

    dfsPostOrderRecursive(root->left);   // 遍历左子树
    dfsPostOrderRecursive(root->right);  // 遍历右子树
    printf("%d ", root->data);           // 访问根节点
}

void dfsPreOrderIterative(TreeNode* root) {
    if (root == NULL) return;
    Stack s;
    initStack(&s);
    push(&s, root);

    while (!isStackEmpty(&s)) {
        TreeNode* current = pop(&s);
        printf("%d", current->data);

        // 栈结构先进后出，如果想先序遍历就要先入栈右子树再入栈左子树
        if (current->right != NULL) {
            push(&s, current->right);
        }
        if (current->left != NULL) {
            push(&s, current->left);
        }
    }
    printf("\n");
}

void dfsInOrderIterative(TreeNode* root) {
    if (root == NULL) return;

    Stack s;
    initStack(&s);
    TreeNode* current = root;

    printf("DFS非递归中序遍历");

    while (current != NULL || !isStackEmpty(&s)) {
        while (current != NULL) {
            push(&s, current);
            current = current->left;
        }

        current = pop(&s);
        printf("%d", current->data);

        current = current->right;
    }
    printf("\n");
}

// DFS非递归后序遍历
void dfsPostOrderIterative(TreeNode* root) {
    if (root == NULL) return;

    Stack s1, s2;
    initStack(&s1);
    initStack(&s2);
    push(&s1, root);

    printf("DFS非递归后序遍历: ");

    // 使用两个栈，s1用于遍历，s2用于反转顺序
    while (!isStackEmpty(&s1)) {
        TreeNode* current = pop(&s1);
        push(&s2, current);

        if (current->left != NULL) {
            push(&s1, current->left);
        }
        if (current->right != NULL) {
            push(&s1, current->right);
        }
    }

    // 从s2弹出节点，得到后序顺序
    while (!isStackEmpty(&s2)) {
        TreeNode* current = pop(&s2);
        printf("%d ", current->data);
    }
    printf("\n");
}

void freeTree(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    // 构建二叉树
    TreeNode* root = buildSampleTree();

    printf("二叉树结构:\n");
    printf("        1\n");
    printf("       / \\\n");
    printf("      2   3\n");
    printf("     / \\   \\\n");
    printf("    4   5   6\n");
    printf("   /\n");
    printf("  7\n\n");

    // BFS遍历
    bfsTraversal(root);
    printf("\n");
    bfsLevelOrder(root);
    printf("\n");

    // DFS递归遍历
    printf("DFS递归先序遍历: ");
    dfsPreOrderRecursive(root);
    printf("\n");

    printf("DFS递归中序遍历: ");
    dfsInOrderRecursive(root);
    printf("\n");

    printf("DFS递归后序遍历: ");
    dfsPostOrderRecursive(root);
    printf("\n\n");

    // DFS非递归遍历
    dfsPreOrderIterative(root);
    dfsInOrderIterative(root);
    dfsPostOrderIterative(root);

    // 释放内存
    freeTree(root);

    return 0;
}