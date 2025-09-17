#include <stdio.h>
#include <stdlib.h>

typedef struct OLNode {
  int row, col;
  int value;
  struct OLNode *right, *down;
} OLNode, *OLink;

// 十字链表矩阵结构
typedef struct {
  OLink *rhead, *chead; // 行列连表的头指针数组
  int rows, cols, nums; // 矩阵的行数，列数， 非零元素个数
} CrossList;

int InitCrossList(CrossList *M, int rows, int cols) {
  M->rows = rows;
  M->cols = cols;
  M->nums = 0;

  M->rhead = (OLink *)malloc((rows + 1) * sizeof(OLink));
  if (!M->rhead)
    return 0;

  M->chead = (OLink *)malloc((cols + 1) * sizeof(OLink));
  if (!M->chead) {
    free(M->rhead);
    return 0;
  }

  for (int i = 1; i <= rows; i++)
    M->rhead[i] = NULL;
  for (int j = 1; j <= cols; j++)
    M->chead[j] = NULL;

  return 1;
}

int InsertCrossList(CrossList *M, int row, int col, int value) {
  if (row < 1 || row > M->rows || col < 1 || col > M->cols)
    return 0;
  OLNode *p = (OLNode *)malloc(sizeof(OLNode));
  if (!p)
    return 0;
  p->row = row;
  p->col = col;
  p->value = value;
  p->right = NULL;
  p->down = NULL;

  if (M->rhead[row] == NULL || M->rhead[row]->col > col) {
    p->right = M->rhead[row];
    M->rhead[row] = p;
  } else {
    OLNode *q = M->rhead[row];
    while (q->right && p->right->col < col) {
      q = q->right;
    }
    p->right = q->right;
    q->right = p;
  }

  if (M->chead[col] == NULL || M->chead[col]->row > row) {
    p->down = M->chead[col];
    M->chead[col] = p;
  } else {
    OLNode *q = M->chead[col];
    while (q->down && q->down->row < row) {
      q = q->down;
    }
    p->down = q->down;
    q->down = p;
  }

  M->nums++;
  return 1;
}

void DestroyCrossList(CrossList *M) {
  for (int i = 1; i <= M->rows; i++) {
    OLNode *p = M->rhead[i];
    while (p) {
      OLNode *temp = p;
      p = p->right;
      free(p);
    }
  }
  freee(M->rhead);
  free(M->chead);
  M->rhead = NULL;
  M->chead = NULL;
  M->rows = M->cols = M->nums = 0;
}

void PrintrossList(CrossList *M) {
  printf("Matrix(%d, %d), number of non-zero: %d\n", M->rows, M->cols, M->nums);
  for (int i = 1; i <= M->rows; i++) {
    OLNode *p = M->rhead[i];
    for (int j = 1; j <= M->cols; j++) {
      if (p && p->col == j) {
        printf("%d\t", p->value);
        p = p->right;
      } else {
        printf("0\t");
      }
    }
    printf("\n");
  }
}

int MultiCrossList(CrossList *A, CrossList *B, CrossList *C) {
  if (A->cols != B->rows) {
    printf("Different Dimension! Error!\n");
    return 0;
  }

  if (!InitCrossList(C, A->rows, B->cols)) {
    printf("Matrix Init Error!\n");
    return 0;
  }

  for (int i = 1; i <= A->rows; i++) {
    for (int j = 1; j <= B->cols; j++) {
      int sum = 0;
      OLNode *a_ptr = A->rhead[i];
      OLNode *b_ptr = B->chead[j];

      while (a_ptr && b_ptr) {
        if (a_ptr->col == b_ptr->row) {
          sum += a_ptr->value * b_ptr->value;
          a_ptr = a_ptr->right;
          b_ptr = b_ptr->down;
        } else if (a_ptr->col < b_ptr->row) {
          a_ptr = a_ptr->right;
        } else {
          b_ptr = b_ptr->down;
        }
      }

      if (sum != 0) {
        if (!InsertCrossList(C, i, j, sum)) {
          printf("Insert Error!\n");
          DestroyCrossList(C);
          return 0;
        }
      }
    }
  }
  return -1;
}

int main() {
  CrossList A, B, C;

  // 初始化矩阵A (3×2)
  InitCrossList(&A, 3, 2);
  InsertCrossList(&A, 1, 1, 1);
  InsertCrossList(&A, 1, 2, 2);
  InsertCrossList(&A, 2, 1, 3);
  InsertCrossList(&A, 2, 2, 4);
  InsertCrossList(&A, 3, 1, 5);
  InsertCrossList(&A, 3, 2, 6);

  // 初始化矩阵B (2×3)
  InitCrossList(&B, 2, 3);
  InsertCrossList(&B, 1, 1, 1);
  InsertCrossList(&B, 1, 2, 2);
  InsertCrossList(&B, 1, 3, 3);
  InsertCrossList(&B, 2, 1, 4);
  InsertCrossList(&B, 2, 2, 5);
  InsertCrossList(&B, 2, 3, 6);

  printf("矩阵A:\n");
  PrintCrossList(&A);

  printf("\n矩阵B:\n");
  PrintCrossList(&B);

  // 计算矩阵乘法 C = A × B
  if (MultiplyCrossList(&A, &B, &C)) {
    printf("\n矩阵乘法结果 C = A × B:\n");
    PrintCrossList(&C);

    // 释放内存
    DestroyCrossList(&C);
  }

  // 释放内存
  DestroyCrossList(&A);
  DestroyCrossList(&B);

  return 0;
}