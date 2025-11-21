#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"

//================= 快速排序 =====================
// 用递归的思路自顶向下，通过枢轴依次拆分区间排序
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 数组，头， 尾
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    // i维护的是一个所有元素都小于枢轴的区间
    // j遍历整个区间，将小于枢轴的元素扔到i维护的区间，同时更新i
    // 最后把枢轴交换到分界线上
    for (int j = low; j <= high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// ========== 冒泡排序 ==========
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < n - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                swapped = 1;
            }
        }
        if (!swapped) break;
    }
}

// ========== 直接插入排序 ==========
// 可以理解成扑克牌抓牌排序，不断拓展一个有序区，新元素加入时向后挪动更大的老元素，把新元素放在合适的位置
void insertSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {  // 逐步拓展有序区
        int key = arr[i];
        int j = i - 1;

        while (j > 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// ========== 希尔排序实现 ==========
// 对元素有间隔的进行直接排序，不断缩小间隔，直到完成排序
void shellSort(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {  // 间隔每次缩小一半，下取整
        // 处理所有满足间隔的数据
        for (int i = gap; i < n; i++) {
            // 这段代码就是直接插入排序
            int temp = arr[i];  // 用temp暂存
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
                // 按照这一次的间隔规则不断的把更大的元素挪到前面
            }
            arr[j] = temp;  // 剩下的一个空放置暂存的arr[i]
        }
    }
}

// ========== 选择排序实现 ==========
// 从第一位开始，遍历该位往后的数组，找到最小元素，记录下标，做交换
void selectSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
}
