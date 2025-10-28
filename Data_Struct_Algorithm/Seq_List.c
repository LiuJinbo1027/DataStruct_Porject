#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int data[100];
  int length;
} SeqList;

void InitSeqList(SeqList *L) { L->length = 0; }

void ReverseSeqList(SeqList *A, SeqList *B) {
  B->length = A->length;

  for (int i = 0; i < A->length; i++) {
    B->data[i] = A->data[A->length - 1 - i];
  }
}

void PrintSeqList(SeqList L) {
  printf("顺序表中的元素为：");
  for (int i = 0; i < L.length; i++) {
    printf("%d", L.data[i]);
  }
  printf("\n");
}

int main() {
  SeqList a, b;
  InitSeqList(&a);
  InitSeqList(&b);

  int arr[] = {1, 2, 3, 4, 5};
  for (int i = 0; i < 5; i++) {
    a.data[i] = arr[i];
    a.length++;
  }

  printf("原顺序表A: ");
  PrintSeqList(a);

  ReverseSeqList(&a, &b);
  printf("逆置后顺序表B: ");
  PrintSeqList(b);

  printf("\n");
}