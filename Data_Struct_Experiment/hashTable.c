#include "stdio.h"
#include "stdlib.h"

int main() {
    int n, p;  // 待储存关键字数量；大于等于n的最小素数
    scanf("%d %d", &n, &p);

    int *keys = (int *)malloc(sizeof(int) * n);   // 关键字表
    int *table = (int *)malloc(sizeof(int) * p);  // 哈希表

    // 初始化哈希表
    for (int i = 0; i < p; i++) {
        table[i] = -1;
    }
    // 录入关键字表
    for (int i = 0; i < n; i++) {
        scanf("%d", &keys[i]);
    }
    // 将关键字逐个录入哈希表
    for (int i = 0; i < n; i++) {
        int key = keys[i];
        int h = key % p;
        int index = h;

        while (1) {
            if (table[index] == -1) {  // 找到空位置，插入关键字
                table[index] = key;
                printf("%d", index);
                break;
            } else if (table[index] == key) {  // 相同关键字已经存在
                printf("%d", index);
                break;
            } else {  // 这个位置被占了
                index = (index + 1) % p;
            }
        }
        if (i < n - 1) {
            printf(" ");
        }
    }
    free(keys);
    free(table);
}