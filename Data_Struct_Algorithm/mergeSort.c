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

    // 考虑到两数组长度不等的情况
    while (i <= mid) {
        temp[k++] = arr[i++];
    }
    while (j <= right) {
        temp[k++] = arr[j++];
    }
    // 用有序数组temp替换原来的两个待归并数组
    k = 0;
    while (left <= right) {
        arr[left++] = temp[k++];
    }
}

// 自底向顶的递归逻辑：先将镇整个无序数组分成单一元素，再将单一元素两两排序，四四排序，直到从下至上完成排序
void mergeSortRecursive(int arr[], int left, int right, int temp[]) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortRecursive(arr, left, mid, temp);
        mergeSortRecursive(arr, mid + 1, right, temp);

        merge(arr, left, mid, right, temp);
    }
}