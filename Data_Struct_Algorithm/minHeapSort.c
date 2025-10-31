#include "stdio.h"
#include "stdlib.h"

// 最小堆化：数组，范围，起点
void minHeapify(int arr[], int n, int i) {
    int smallest = i;       // 初始化最小元素为根节点
    int left = 2 * i + 1;   // 其左节点在数组中的位置
    int right = 2 * i + 2;  // 其右节点在数组中的位置
    if (left < n && arr[left] < arr[smallest]) {  // 若：左节点存在 且 更小
        smallest = left;
    }
    if (right < n && arr[right] < arr[smallest]) {
        smallest = right;
    }
    if (smallest != i) {
        int temp = arr[smallest];
        arr[smallest] = arr[i];
        arr[i] = temp;
        // smallest被放入了原来更大的根节点，要检查新smallest的子树是否符合最小堆
        minHeapify(arr, n, smallest);
    }
}

void buildHeap(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        minHeapify(arr, n, i);  // 从最后一个非叶子节点开始逐个构建最小堆
    }
}

void minHeapSort(int arr[], int n) {
    buildHeap(arr, n);

    for (int i = n; i > 0; i--) {
        // 将根节点放到队尾
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        // 不考虑扔到队尾的最小值，重新堆化，把新的最小值放到堆顶
        minHeapify(arr, i, 0);
    }
}