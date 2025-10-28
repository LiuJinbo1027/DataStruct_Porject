#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode {
    char data;
    struct TreeNode* right;
    struct TreeNode* left;
} TreeNode;

// 递归构建二叉树
TreeNode* buildTree(char* preorder, char* inorder, int n) {
    if (n == 0) return NULL;
    // 先序遍历的第一个节点是根节点
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->data = preorder[0];
    root->left = NULL;
    root->right = NULL;

    // 在中序遍历中找到根节点的位置
    int rootIndex = 0;
    for (int i = 0; i < n; i++) {
        if (inorder[i] == preorder[0]) {
            rootIndex = i;
            break;
        }
    }

    // 递归构建子树
    root->left = buildTree(preorder + 1, inorder, rootIndex);
    root->right = buildTree(preorder + rootIndex + 1, inorder + rootIndex + 1,
                            n - rootIndex - 1);

    return root;
}

int getHeight(TreeNode* root) {
    if (root == NULL) {
        return 0;
    }

    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);

    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int countLeaves(TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    if (root->left == NULL && root->right == NULL) {
        return 1;
    }
    return countLeaves(root->right) + countLeaves(root->left);
}

void freeTree(TreeNode* root) {
    if (root == NULL) return;

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    int n;
    char preorder[50];
    char inorder[50];

    scanf("%s", preorder);
    scanf("%s", inorder);
    n = strlen(preorder);

    TreeNode* root = buildTree(preorder, inorder, n);

    int height = getHeight(root);
    printf("%d\n", height);
    int leaves = countLeaves(root);
    printf("%d\n", leaves);

    freeTree(root);
    return 0;
}