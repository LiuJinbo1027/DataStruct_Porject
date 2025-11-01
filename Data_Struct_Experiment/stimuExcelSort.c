#include <stdio.h>

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct {
    char id[7];
    char name[9];
    int score;
} Student;

void swap(Student *a, Student *b) {
    Student temp = *a;
    *a = *b;
    *b = temp;
}

int partitionById(Student arr[], int low, int high) {
    char *pivot = arr[high].id;  // 选择最后一个元素作为枢轴
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (strcmp(arr[j].id, pivot) < 0) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSortById(Student arr[], int low, int high) {
    if (low < high) {
        int pi = partitionById(arr, low, high);
        quickSortById(arr, low, pi);
        quickSortById(arr, pi + 1, high);
    }
}

void quickSortByName(Student arr[], int low, int high) {
    if (low < high) {
        Student pivot = arr[high];
        int i = low - 1;

        for (int j = low; j <= high; j++) {
            int nameCmp = strcmp(arr[j].name, pivot.name);
            if (nameCmp < 0 ||
                (nameCmp = 0 && strcmp(arr[j].id, pivot.id) < 0)) {
                i++;
                swap(&arr[i], &arr[j]);
            }
        }
        swap(&arr[i + 1], &arr[high]);
        int pi = i + 1;

        quickSortByName(arr, low, high);
        quickSortByName(arr, pi + 1, high);
    }
}

void quickSortByScore(Student arr[], int low, int high) {
    if (low < high) {
        Student pivot = arr[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (arr[j].score < pivot.score ||
                (arr[j].score == pivot.score &&
                 strcmp(arr[j].id, pivot.id) < 0)) {
                i++;
                swap(&arr[i], &arr[j]);
            }
        }
        swap(&arr[i + 1], &arr[high]);
        int pi = i + 1;
        quickSortByScore(arr, low, pi);
        quickSortByScore(arr, pi + 1, high);
    }
}

int main() {
    int N, C;
    scanf("%d %d", &N, &C);
    Student *students = (Student *)malloc(sizeof(Student));

    for (int i = 0; i < N; i++) {
        scanf("%s %s %d", students[i].id, students[i].name, &students[i].score);
    }

    switch (C) {
        case 1:
            quickSortById(students, 0, N - 1);
            break;
        case 2:
            quickSortByName(students, 0, N - 1);
            break;
        case 3:
            quickSortByScore(students, 0, N - 1);
            break;
        default:
            break;
    }

    for (int i = 0; i < N; i++) {
        printf("%s %s %d\n", students[i].id, students[i].name,
               students[i].score);
    }

    free(students);
    return 0;
}