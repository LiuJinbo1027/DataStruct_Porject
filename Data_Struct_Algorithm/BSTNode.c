#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BSTNode {
    int data;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

BSTNode *createNode(int data) {
    BSTNode *newNode = (BSTNode *)malloc(sizeof(BSTNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 递归插入新节点
BSTNode *insertRecursive(BSTNode *root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = insertRecursive(root->left, data);
    } else if (data > root->data) {
        root->right = insertRecursive(root->right, data);
    }

    return root;
}

// 迭代插入新节点
void insertIterative(BSTNode **root, int data) {
    BSTNode *newNode = createNode(data);

    if (*root == NULL) {
        *root = newNode;
        return;
    }
    BSTNode *current = *root;
    BSTNode *parent = NULL;

    while (current != NULL) {
        parent = current;

        if (data < current->data) {
            current = current->left;
        } else if (data > current->data) {
            current = current->right;
        } else {
            free(newNode);  // 数据已存在，释放内存并返回
            return;
        }
    }

    if (data < parent->data) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
}

// 递归查找节点
BSTNode *searchRecursive(BSTNode *root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }
    if (data < root->data) {
        return searchRecursive(root->left, data);
    } else {
        return searchRecursive(root->right, data);
    }
}

// 迭代查找节点
BSTNode *searchIteractive(BSTNode *root, int data) {
    BSTNode *current = root;

    while (current != NULL && current->data != data) {
        if (data < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return current;
}

// 找到最小值
BSTNode *findMin(BSTNode *root) {
    if (root == NULL) return NULL;

    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// 找到最大值
BSTNode *findMax(BSTNode *root) {
    if (root == NULL) return NULL;

    while (root->right != NULL) {
        root = root->right;
    }
    return root;
}

// 删除节点
BSTNode *deleteNode(BSTNode *root, int data) {
    if (root == NULL) return root;

    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    } else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    } else {  // 找到了要删除的节点
        // 情况一：节点是叶子节点 或者 已有一个子节点
        if (root->left == NULL) {
            BSTNode *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            BSTNode *temp = root->left;
            free(root);
            return temp;
        }
        // 情况二：节点有两个子节点
        // 找到右子树最小节点 或 左子树最大节点
        BSTNode *temp = findMin(root->right);
        // 用最小节点的值替代当前节点的值
        root->data = temp->data;
        // 删除右子树中的最小节点
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// 前序遍历
void preorderTraversal(BSTNode *root) {
    if (root == NULL) return;

    printf("%d", root->data);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

// 中序遍历：得到升序序列
void inorderTraversal(BSTNode *root) {
    if (root == NULL) return;

    inorderTraversal(root->left);
    printf("%d", root->data);
    inorderTraversal(root->right);
}

// 后序遍历
void postorderTraversal(BSTNode *root) {
    if (root == NULL) return;

    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("%d ", root->data);
}

int getHeight(BSTNode *root) {
    if (root == NULL) return 0;

    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);

    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int countNodes(BSTNode *root) {
    if (root == NULL) return 0;

    return 1 + countNodes(root->left) + countNodes(root->right);
}

void freeTree(BSTNode *root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}
