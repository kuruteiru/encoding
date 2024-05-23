#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdbool.h>
#include <inttypes.h>

typedef struct MinHeapNode {
    struct MinHeapNode *left, *right;
    float frequency;
    char value;
} MinHeapNode;

MinHeapNode* newMinHeapNode(char value, float frequency);

void swapMinHeapNodes(MinHeapNode **nodeA, MinHeapNode **nodeB);

bool isLeaf(MinHeapNode *node);

typedef struct MinHeap {
    MinHeapNode **nodes;
    uint32_t capacity;
    uint32_t size;
} MinHeap;

MinHeap* newMinHeap(uint32_t capacity);
MinHeap* initializeMinHeap(char values[], float frequencies[], uint32_t capacity);

void insertMinHeapNode(MinHeap *self, MinHeapNode *node);
void minHeapify(MinHeap *self, uint32_t index);
void minHeapifyNonLeaves(MinHeap *self);

MinHeapNode* getMinimum(MinHeap *self);
MinHeapNode* buildHuffmanTree(char values[], float frequencies[], uint32_t capacity);

void printCodes(MinHeapNode *node, uint8_t codeBuffer[], uint32_t index);
void huffmanEncode(char values[], float frequencies[], uint32_t capacity);

#endif //HUFFMAN_H