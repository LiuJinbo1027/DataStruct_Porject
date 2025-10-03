#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int coeff;
    int exp;
    struct Node* next;
} Node;

Node* createNewNode(int coeff, int exp) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = NULL;
    return newNode;
}

Node* createPolynomial(int data[], int n) {
    if (n == 0) {
        return NULL;
    }

    Node* head = createNewNode(data[0], data[1]);
    Node* current = head;

    for (int i = 2; i < n; i += 2) {
        Node* newNode = createNewNode(data[i], data[i + 1]);
        current->next = newNode;
        current = newNode;
    }

    return head;
}

Node* derivative(Node* polyHead) {
    Node* newHead = NULL;
    Node* currentNew = NULL;
    Node* current = polyHead;

    while (current != NULL) {
        if (current->exp != 0) {
            int newCoeff = current->coeff * current->exp;
            int newExp = current->exp - 1;
            Node* newNode = createNewNode(newCoeff, newExp);
            if (newHead == NULL) {
                newHead = newNode;
                currentNew = newHead;
            } else {
                currentNew->next = newNode;
                currentNew = newNode;
            }
            current = current->next;
        }

        if (newHead == NULL) {
            newHead = createNewNode(0, 0);
        }
    }
    return newHead;
}

void printPolynomial(Node* polyHead) {
    Node* current = polyHead;
    int first = 1;
    while (current != NULL) {
        if (!first) {
            printf(" ");
        }
        printf("%d %d", current->coeff, current->exp);
        first = 0;
        current = current->next;
    }
}

void freeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    int data[2000];
    int count = 0;
    int num = 0;

    while (scanf("%d", &num) != "\n") {
        data[count++] = num;
    }

    if (count == 0) {
        printf("0 0");
        return 0;
    }
    Node* polyhead = createPolynomial(data, count);

    Node* derhead = derivative(polyhead);

    printPolynomial(derhead);
}