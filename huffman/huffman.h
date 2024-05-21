#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdbool.h>

typedef struct MinHeapNode {
    struct MinHeapNode *left, *right;
    unsigned int frequency;
    char value;
} MinHeapNode;

MinHeapNode* newMinHeapNode(char value, unsigned int frequency);

void swapMinHeapNodes(MinHeapNode **a, MinHeapNode **b);

bool isLeaf(MinHeapNode *node);

typedef struct MinHeap {
    MinHeapNode **array;
    unsigned int capacity;
    unsigned int size;
} MinHeap;

MinHeap* initializeMinHeap(unsigned int capacity);

void minHeapify(MinHeap *self, int index);
void insertMinHeapNode(MinHeap *self, MinHeapNode *node);
void buildMinHeap(MinHeap *self);

MinHeapNode* getMinimum(MinHeap *self);
MinHeapNode* BuildHuffmanTree();

void printIntArray();
void printCodes(MinHeapNode *root, int codes[], int index);

void huffmanEncode(char values[], int frequencies[], int size);

#endif //HUFFMAN_H