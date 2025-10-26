#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stdbool.h"

typedef struct AVLNode {
    int data;
    int height;
    struct AVLNode* left;
    struct AVLNode* right;
} AVLNode;

// 获取节点高度
int getHeight(AVLNode* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

int max(int a, int b) { return (a > b) ? a : b; }

// 计算平衡因子
int getBalance(AVLNode* node) {
    if (node == NULL) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

AVLNode* createNode(int data) {
    AVLNode* newNode = (AVLNode*)malloc(sizeof(AVLNode));
    newNode->data = data;
    newNode->height = 1;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 右旋操作
AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight((x->right))) + 1;

    return x;
}

// 左旋操作
AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

AVLNode* minValueNode(AVLNode* node) {
    AVLNode* current = node;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

AVLNode* searchNode(AVLNode* root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }

    if (data < root->data) {
        return searchNode(root->left, data);
    } else {
        return searchNode(root->right, data);
    }
}

void inOrder(AVLNode* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

void preOrder(AVLNode* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        inOrder(root->left);
        inOrder(root->right);
    }
}

// 插入节点
AVLNode* insert(AVLNode* node, int data) {
    // 1.标准BFS节点插入: 把节点挂到树上
    if (node == NULL) {
        return createNode(data);
    }
    if (data < node->data) {
        node->left = insert(node->left, data);
    } else if (data > node->data) {
        node->right = insert(node->right, data);
    } else {
        return node;
    }

    // 更新节点高度：node是根
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    // 获取平衡因子检查是否失衡
    int balance = getBalance(node);
    // 如果节点失衡，可分为四种情况处理
    // LL
    if (balance > 1 && data < node->left->data) {
        // 根节点左子树过长 且 其左子节点左失衡（新节点被挂在了左节点的左子树）
        return rightRotate(node);
    }
    // RR
    if (balance < -1 && data > node->right->data) {
        return leftRotate(node);
    }
    // LR
    if (balance > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    // RL
    if (balance < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

AVLNode* deleteNode(AVLNode* root, int data) {
    if (root == NULL) {
        return root;
    }
    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    } else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    } else {  // 找到要删除的节点
        if (root->left == NULL ||
            root->right == NULL) {  // 节点有一个或者没有子节点
            AVLNode* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp);
        } else {  // 节点有两个子节点
            // 可以找待删除节点右子树的最小值 或者 左子树的最大值
            // 这里选择前者
            AVLNode* temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }

    if (root == NULL) {
        return root;
    }

    root->height = max(getHeight(root->right), getHeight(root->left)) + 1;
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0) {
        return rightRotate(root);
    }
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0) {
        return leftRotate(root);
    }
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}
