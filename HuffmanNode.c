#include <limits.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 哈夫曼树结构
typedef struct HuffmanNode {
    int weight;
    struct HuffmanNode *left;
    struct HuffmanNode *right;
} HuffmanNode;

// 最小堆结构
typedef struct MinHeap {
    int size;             // 堆当前大小
    int capacity;         // 堆容量
    HuffmanNode **array;  // 节点指针数组
} MinHeap;

// 创建新节点
HuffmanNode *createNode(int weight) {
    HuffmanNode *node = (HuffmanNode *)malloc(sizeof(HuffmanNode));
    node->weight = weight;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// 创建最小堆
MinHeap *createMinHeap(int capacity) {
    MinHeap *heap = (MinHeap *)malloc(sizeof(MinHeap));
    heap->size = 0;
    heap->capacity = capacity;
    heap->array = (HuffmanNode **)malloc(capacity * sizeof(HuffmanNode *));
    return heap;
}

// 交换两个节点
void swapNodes(HuffmanNode **a, HuffmanNode **b) {
    HuffmanNode *temp = *a;
    *a = *b;
    *b = temp;
}

// 最小堆化（向下调整）
void minHeapify(MinHeap *heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size &&
        heap->array[left]->weight < heap->array[smallest]->weight)
        smallest = left;

    if (right < heap->size &&
        heap->array[right]->weight < heap->array[smallest]->weight)
        smallest = right;

    if (smallest != idx) {
        swapNodes(&heap->array[smallest], &heap->array[idx]);
        minHeapify(heap, smallest);
    }
}

// 检查堆大小是否为1
int isSizeOne(MinHeap *heap) { return heap->size == 1; }

// 提取最小节点
HuffmanNode *extractMin(MinHeap *heap) {
    HuffmanNode *temp = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    --heap->size;
    minHeapify(heap, 0);
    return temp;
}

// 插入节点到最小堆
void insertMinHeap(MinHeap *heap, HuffmanNode *node) {
    ++heap->size;
    int i = heap->size - 1;

    while (i && node->weight < heap->array[(i - 1) / 2]->weight) {
        heap->array[i] = heap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    heap->array[i] = node;
}

// 构建最小堆
void buildMinHeap(MinHeap *heap) {
    int n = heap->size - 1;
    for (int i = (n - 1) / 2; i >= 0; --i) minHeapify(heap, i);
}

// 创建最小堆并初始化
MinHeap *createAndBuildMinHeap(int weights[], int size) {
    MinHeap *heap = createMinHeap(size);
    for (int i = 0; i < size; ++i) heap->array[i] = createNode(weights[i]);
    heap->size = size;
    buildMinHeap(heap);
    return heap;
}

HuffmanNode *buildHuffmanTree(int weights[], int size) {
    HuffmanNode *left, *right, *top;

    // 创建最小堆
    MinHeap *heap = createAndBuildMinHeap(weights, size);

    while (!isSizeOne(heap)) {
        left = extractMin(heap);
        right = extractMin(heap);

        // 创建新节点，权值为两个最小节点之和
        top = createNode(left->weight + right->weight);
        top->left = left;
        top->right = right;

        insertMinHeap(heap, top);
    }

    return extractMin(heap);
}

void printHuffmanTree(HuffmanNode *root, int level) {
    if (root == NULL) return;

    for (int i = 0; i < level; i++) printf("  ");

    if (root->left == NULL && root->right == NULL)
        printf("权重： %d (叶子)\n", root->weight);
    else
        printf("权重：%d\n", root->weight);

    printHuffmanTree(root->left, level + 1);
    printHuffmanTree(root->right, level + 1);
}

int getHuffmanTreeHeight(HuffmanNode *root) {
    if (root == NULL)
        return 0;
    else {
        int leftHeight = getHuffmanTreeHeight(root->left);
        int rightheight = getHuffmanTreeHeight(root->right);
        return (leftHeight > rightheight ? leftHeight : rightheight) + 1;
    }
}

// 计算WPL
int calculateWPL(HuffmanNode *root, int depth) {
    if (root == NULL) return 0;
    // 如果是叶子节点
    if (root->left == NULL && root->right == NULL) return root->weight * depth;

    // 递归计算左右子树
    return calculateWPL(root->left, depth + 1) +
           calculateWPL(root->right, depth + 1);
}

void freeHuffmanTree(HuffmanNode *root) {
    if (root == NULL) return;
    freeHuffmanTree(root->left);
    freeHuffmanTree(root->right);
    free(root);
}

int main() {
    int n;
    printf("请输入数字的个数：");
    scanf("%d", &n);

    int *weights = (int *)malloc(sizeof(int));
    printf("请输入%d个数字（作为权重）: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &weights[i]);
    }

    // 构建哈夫曼树
    HuffmanNode *root = buildHuffmanTree(weights, n);

    // 输出结果
    printf("\n哈夫曼树结构:\n");
    printHuffmanTree(root, 0);

    printf("\n哈夫曼树高度: %d\n", getHuffmanTreeHeight(root));
    printf("带权路径长度(WPL): %d\n", calculateWPL(root, 0));

    // 清理内存
    freeHuffmanTree(root);
    free(weights);

    return 0;
}