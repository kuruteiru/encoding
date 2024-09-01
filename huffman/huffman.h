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

void printHuffmanTree(MinHeapNode *node, uint32_t depth, uint8_t codeBuffer[]);
void printHuffmanTable(MinHeapNode *node, uint32_t index, uint8_t codeBuffer[]);

void huffmanEncode(char values[], float frequencies[], uint32_t capacity);

float getAverageHuffmanCodeLength(MinHeapNode *root);
float calculateTotalHuffmanFrequency(MinHeapNode *root);
float calculateHuffmanEntropyRecursive(MinHeapNode *root, float totalFrequency);
float calculateHuffmanEntropy(MinHeapNode *root);
float getHuffmanCodeEffectivity(MinHeapNode *root);

#endif //HUFFMAN_H
