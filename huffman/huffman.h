#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdbool.h>

typedef struct MinHeapNode {
    struct MinHeapNode *left, *right;
    unsigned int frequency;
    char value;
} MinHeapNode;

MinHeapNode* newMinHeapNode(char value, unsigned int frequency);

void swapMinHeapNodes(MinHeapNode **nodeA, MinHeapNode **nodeB);

bool isLeaf(MinHeapNode *node);

typedef struct MinHeap {
    MinHeapNode **nodes;
    unsigned int capacity;
    unsigned int size;
} MinHeap;

MinHeap* newMinHeap(unsigned int capacity);
MinHeap* initializeMinHeap
(char values[], unsigned int frequencies[], unsigned int capacity);

void insertMinHeapNode(MinHeap *self, MinHeapNode *node);
void minHeapify(MinHeap *self, unsigned int index);
void minHeapifyNonLeaves(MinHeap *self);

MinHeapNode* getMinimum(MinHeap *self);
MinHeapNode* buildHuffmanTree
(char values[], unsigned int frequencies[], unsigned int capacity);

void printCodes(MinHeapNode *node, unsigned int codes[], unsigned int index);
void huffmanEncode(char values[], int frequencies[], unsigned int capacity);

#endif //HUFFMAN_H