#include "stdio.h"
#include "stdlib.h"

// 合并两个有序数组
void merge(int arr[], int left, int mid, int right, int temp[]) {
    int i = left;     // 左子数组起始位置
    int j = mid + 1;  // 右子数组起始位置
    int k = 0;        // 临时数组索引

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = arr[i++];
    }
    while (j <= right) {
        temp[k++] = arr[j++];
    }

    k = 0;
    while (left <= right) {
        arr[left++] = temp[k++];
    }
}

void mergeSortRecursive(int arr[], int left, int right, int temp[]) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortRecursive(arr, left, mid, temp);
        mergeSortRecursive(arr, mid + 1, right, temp);

        merge(arr, left, mid, right, temp);
    }
}