#include <stdio.h>
#include <stdlib.h>

typedef struct ThreadedTreeNode {
    char data;
    struct ThreadedTreeNode *left;
    struct ThreadedTreeNode *right;
    int ltag;
    int rtag;
} ThreadedTreeNode;

ThreadedTreeNode *pre = NULL;

ThreadedTreeNode *createNode(char data) {
    ThreadedTreeNode *newNode =
        (ThreadedTreeNode *)malloc(sizeof(ThreadedTreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->ltag = 0;
    newNode->rtag = 0;
    return newNode;
}

// 基于中序遍历的线索二叉树构建
void inThreading(ThreadedTreeNode *p) {
    if (p != NULL) {
        inThreading(p->left);  // 递归处理左子树

        // 处理当前节点的前驱线索
        if (p->left == NULL) {
            p->ltag = 1;    // 标记为线索
            p->left = pre;  // 指向前驱节点
        } else {
            p->ltag = 0;
        }

        // 处理其前驱节点的后继线索
        if (pre != NULL && pre->right == NULL) {
            pre->rtag = 1;
            pre->right = p;  // 该节点的前驱节点 的后继节点 是该节点
        }
        pre = p;                // 更新前驱节点
        inThreading(p->right);  // 递归处理右子树
    }
}

// 创建头节点并线索化二叉树
void createInorderThreadedTree(ThreadedTreeNode **head,
                               ThreadedTreeNode *root) {
    *head = (ThreadedTreeNode *)malloc(sizeof(ThreadedTreeNode));
    (*head)->ltag = 0;
    (*head)->rtag = 1;
    (*head)->right = *head;

    if (root == NULL) {
        (*head)->left = *head;
    } else {
        (*head)->left = root;
        pre = *head;
    }

    inThreading(root);

    pre->rtag = 1;
    pre->right = *head;

    (*head)->right = pre;
}

// 非递归中序遍历线索二叉树
void inorderTraverseThreadedTree(ThreadedTreeNode *head) {
    ThreadedTreeNode *p = head->left;  // 指向根节点

    while (p != head) {
        // 找到最左下的节点
        while (p->ltag == 0) {
            p = p->left;
        }

        // 访问节点
        printf("%c ", p->data);

        // 如果有后继线索，一直访问
        while (p->rtag == 1 && p->right != head) {
            p = p->right;
            printf("%c ", p->data);
        }

        // 转向右子树
        p = p->right;
    }
    printf("\n");
}

ThreadedTreeNode *buildSampleTree() {
    ThreadedTreeNode *root = createNode('A');
    root->left = createNode('B');
    root->right = createNode('C');
    root->left->left = createNode('D');
    root->left->right = createNode('E');
    root->right->left = createNode('F');
    root->right->right = createNode('G');
    root->left->right->left = createNode('H');
    root->left->right->right = createNode('I');
    return root;
}

void freeThreadedTree(ThreadedTreeNode *head) {
    if (head == NULL) return;
    ThreadedTreeNode *p = head->left;
    ThreadedTreeNode *temp;

    while (p != head) {
        while (p->ltag == 0) {
            p = p->left;
        }
        temp = p;

        while (p->rtag == 1 && p->right != head) {
            p = p->right;
            free(temp);
            temp = p;
        }

        p = p->right;
        free(temp);
    }

    free(head);
}

int main() {
    // 构建二叉树
    ThreadedTreeNode *root = buildSampleTree();

    // 创建线索二叉树
    ThreadedTreeNode *head = NULL;
    createInorderThreadedTree(&head, root);

    // 中序遍历线索二叉树
    printf("中序遍历线索二叉树: ");
    inorderTraverseThreadedTree(head);

    // 释放内存
    freeThreadedTree(head);

    return 0;
}