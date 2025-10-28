#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
  char data;
  struct TreeNode *left;
  struct TreeNode *right;
} TreeNode;

TreeNode *createNode(char data) {
  TreeNode *newnode = (TreeNode *)malloc(sizeof(TreeNode));
  newnode->data = data;
  newnode->left = NULL;
  newnode->right = NULL;
  return newnode;
}

void preorderTraversal(TreeNode *root) {
  if (root == NULL)
    return;
  printf("%c ", root->data);
  preorderTraversal(root->left);
  preorderTraversal(root->right);
}

void inorderTraversal(TreeNode *root) {
  if (root == NULL)
    return;
  inorderTraversal(root->left);
  printf("%c ", root->data);
  inorderTraversal(root->right);
}

void postorderTraversal(TreeNode *root) {
  if (root == NULL)
    return;
  postorderTraversal(root->left);
  postorderTraversal(root->right);
  printf("%c ", root->data);
}

TreeNode *buildSampleTree() {
  TreeNode *root = createNode('A');
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

void freeTree(TreeNode *root) {
  if (root == NULL)
    return;
  freeTree(root->left);
  freeTree(root->right);
  free(root);
}

int main() {
  // 构建二叉树
  TreeNode *root = buildSampleTree();

  // 输出遍历结果
  printf("前序遍历: ");
  preorderTraversal(root);
  printf("\n");

  printf("中序遍历: ");
  inorderTraversal(root);
  printf("\n");

  printf("后序遍历: ");
  postorderTraversal(root);
  printf("\n");

  // 释放内存
  freeTree(root);

  return 0;
}