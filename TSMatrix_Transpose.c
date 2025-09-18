#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 1000

typedef struct {
  int row, col;
  int value;
} Triple;

typedef struct {
  Triple data[MAXSIZE + 1];
  int rows, cols, nums;
} TSMatrix;

// 创建稀疏矩阵
void CreateMatrix(TSMatrix *M) {
  printf("请输入矩阵的行数、列数和非零元素个数: ");
  scanf("%d %d %d", &M->rows, &M->cols, &M->nums);

  printf("请按行优先顺序输入%d个非零元素(行 列 值):\n", M->nums);
  for (int i = 1; i <= M->nums; i++) {
    scanf("%d %d %d", &M->data[i].row, &M->data[i].col, &M->data[i].value);
  }
}

// 打印稀疏矩阵
void PrintTSMatrix(TSMatrix M) {
  printf("稀疏矩阵(%dx%d)，非零元素个数：%d\n", M.rows, M.cols, M.nums);
  printf("行\t列\t值\n");
  for (int i = 1; i <= M.nums; i++) {
    printf("%d\t%d\t%d\n", M.data[i].row, M.data[i].col, M.data[i].value);
  }
}

// 转置算法：跳着找，顺序存
void TransposeTSMatrix(TSMatrix M, TSMatrix *T) {
  T->rows = M.cols;
  T->cols = M.rows;
  T->nums = M.nums;

  if (T->nums == 0)
    return;

  int q = 1;
  for (int col = 1; col <= M.cols; col++) {
    for (int p = 1; p <= M.nums; p++) {
      if (M.data[p].col == col) {
        T->data[q].row = M.data[p].col;
        T->data[q].col = M.data[p].row;
        T->data[q].value = M.data[p].value;
        q++;
      }
    }
  }
}

// 优化的转置算法：顺着找，跳着存
void FastTransposeTSMatrix(TSMatrix M, TSMatrix *T) {
  T->rows = M.cols;
  T->cols = M.rows;
  T->nums = M.nums;

  if (T->nums == 0)
    return;

  int num[MAXSIZE] = {0};
  for (int i = 1; i <= M.nums; i++) {
    num[M.data[i].col]++;
  }

  int cpot[MAXSIZE] = {0};
  cpot[1] = 1;
  for (int col = 2; col <= M.cols; col++) {
    cpot[col] = cpot[col - 1] + num[col - 1];
  }

  // 进行转置
  for (int p = 1; p <= M.nums; p++) {
    int col = M.data[p].col;
    int q = cpot[col];

    T->data[q].row = M.data[p].col;
    T->data[q].col = M.data[p].row;
    T->data[q].value = M.data[p].value;

    cpot[col]++; // 更新当前位置
  }
}

// 打印矩阵的常规形式（便于查看结果）
void PrintMatrix(TSMatrix M) {
  int k = 1; // 指向当前非零元素

  printf("矩阵的常规形式(%d×%d):\n", M.rows, M.cols);
  for (int i = 1; i <= M.rows; i++) {
    for (int j = 1; j <= M.cols; j++) {
      if (k <= M.nums && M.data[k].row == i && M.data[k].col == j) {
        printf("%d\t", M.data[k].value);
        k++;
      } else {
        printf("0\t");
      }
    }
    printf("\n");
  }
}

int main() {
  TSMatrix M, T1, T2;

  // 创建稀疏矩阵
  CreateTSMatrix(&M);

  printf("\n原矩阵:\n");
  PrintTSMatrix(M);
  PrintMatrix(M);

  // 使用简单转置算法
  TransposeTSMatrix(M, &T1);
  printf("\n简单转置结果:\n");
  PrintTSMatrix(T1);
  PrintMatrix(T1);

  // 使用快速转置算法
  FastTransposeTSMatrix(M, &T2);
  printf("\n快速转置结果:\n");
  PrintTSMatrix(T2);
  PrintMatrix(T2);

  return 0;
}
