#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void kmp(char *str, char *sub, int *next, int sub_size, int str_size) {
    int i = 0;
    int j = 0;
    int index = -1;
    while (i < str_size) {
        if (j == sub_size) {
            index = i;
            break;
        }
        if (j == -1 || str[i] == sub[j]) {
            i++;
            j++;
        } else {
            j = next[j];
        }
    }
}
void computeNext(char *P, int p_size, int *next) {
    next[0] = -1;
    int i = 0, k = -1;  //上次匹配的长度
    while (i < p_size - 1) {
        if (k == -1 || P[i] == P[k]) {
            i++;
            k++;
            next[i] = k;
        } else {
            k = next[k];
        }
    }
}
int main() {
    char str[111];
    char sub[5];
    scanf("%s", str);
    scanf("%s", sub);
    int str_size = strlen(str);
    int sub_size = strlen(sub);
    int next[sub_size];
    computeNext(sub, sub_size, next);
    kmp(str, sub, next, sub_size, str_size);
    return 0;
}