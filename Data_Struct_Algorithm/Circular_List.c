#include <stdio.h>
#include <stdlib.h>

typedef struct CNode {
  int data;
  struct CNode *next;
} CNode, *CircularList;

void InitCircularList(CircularList *L) {
  *L = (CircularList)malloc(sizeof(CNode));
  (*L)->next = *L; // 指向自己，形成循环
}

int GetLength(CircularList L) {
  int count = 0;
  CNode *p = L->next;

  while (p != L) {
    count++;
    p = p->next;
  }

  return count;
}

int Insert(CircularList L, int i, int e) {
  if (i < 1)
    return 0;

  CNode *p = L;
  int j = 0;
  while (p->next != L && j < i - 1) {
    p = p->next;
    j++;
  }
  CNode *s = (CNode *)malloc(sizeof(CNode *));
  s->data = e;
  s->next = p->next;
  p->next = s;

  return 1;
}

int Delete(CircularList L, int i, int *e) {
  if (i < 1)
    return 0; // 位置非法

  CNode *p = L;
  int j = 0;

  // 寻找第i-1个结点
  while (p->next != L && j < i - 1) {
    p = p->next;
    j++;
  }

  if (j != i - 1 || p->next == L)
    return 0; // 位置超出范围或为空表

  CNode *q = p->next;
  *e = q->data;
  p->next = q->next;
  free(q);

  return 1;
}

int GetElem(CircularList L, int i, int *e) {
  if (i < 1)
    return 0; // 位置非法

  CNode *p = L->next;
  int j = 1;

  // 寻找第i个结点
  while (p != L && j < i) {
    p = p->next;
    j++;
  }

  if (p == L || j > i)
    return 0; // 位置超出范围

  *e = p->data;
  return 1;
}

void PrintCircularList(CircularList L) {
  CNode *p = L->next;
  printf("循环单链表元素: ");

  while (p != L) {
    printf("%d ", p->data);
    p = p->next;
  }
  printf("\n");
}

void DestroyCircularList(CircularList L) {
  CNode *p = L->next;
  CNode *q;

  // 释放所有数据结点
  while (p != L) {
    q = p->next;
    free(p);
    p = q;
  }

  // 释放头结点
  free(L);
}

int main() {

  CircularList L;
  InitCircularList(&L);

  // 测试插入操作
  for (int i = 1; i <= 5; i++) {
    Insert(L, i, i * 10);
  }

  printf("插入元素后: ");
  PrintCircularList(L);
  printf("链表长度: %d\n", GetLength(L));

  // 测试获取元素操作
  int elem;
  if (GetElem(L, 3, &elem)) {
    printf("第3个元素: %d\n", elem);
  }

  // 测试删除操作
  int deletedElem;
  if (Delete(L, 2, &deletedElem)) {
    printf("删除第2个元素: %d\n", deletedElem);
    printf("删除后链表: ");
    PrintCircularList(L);
  }

  DestroyCircularList(L);
  printf("\n");
}