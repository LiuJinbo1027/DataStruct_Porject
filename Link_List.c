#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  int data;
  struct Node *next;
} Node, *Linklist;

void InitLinkList(Linklist *L) {
  *L = (Linklist)malloc(sizeof(Node));
  (*L)->next = NULL;
}

void CreateLinkListHead(Linklist L, int a[], int n) {
  Node *s;
  for (int i = 0; i < n; i++) {
    s = (Node *)malloc(sizeof(Node));
    s->data = a[i];
    s->next = L->next;
    L->next = s;
  }
}

void ReverseLinkList(Linklist L) {
  if (L->next == NULL || L->next->next == NULL) {
    return;
  }
  Node *p = L->next; // 第一个数据节点
  Node *q;
  L->next = NULL; // 将头节点与原链表断开

  while (p != NULL) {
    q = p->next;
    p->next = L->next;
    L->next = p;
    p = q;
  }
}

void PrintLinkList(Linklist L) {
  Node *p = L->next;
  while (p != NULL) {
    printf("%d", p->data);
    p = p->next;
  }
  printf("\n");
}

void DestroyLinkList(Linklist L) {
  Node *p = L, *q;
  while (p != NULL) {
    q = p->next;
    free(p);
    p = q;
  }
}

int main() {
  Linklist L;
  InitLinkList(&L);

  int arr[] = {1, 2, 3, 4, 5};
  CreateLinkListHead(L, arr, 5);

  printf("原单链表: ");
  PrintLinkList(L);

  ReverseLinkList(L);
  printf("逆置后单链表: ");
  PrintLinkList(L);

  DestroyLinkList(L);
  printf("\n");
}