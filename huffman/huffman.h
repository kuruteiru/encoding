#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <inttypes.h>

typedef struct BitStream {
    uint8_t bits[8];
} BitStream;

typedef struct MinHeapNode {
    char data;
    unsigned int frequency;
    struct HuffmanNode *left, *right;
} MinHeapNode;

MinHeapNode* newMinHeapNode(char data, unsigned int frequency);

void swapMinHeapNodes(MinHeapNode **a, MinHeapNode **b);

typedef struct MinHeap {
    unsigned int size;
    unsigned int capacity;
    MinHeapNode **array;
} MinHeap;

MinHeap* initializeMinHeap(unsigned int capacity);

void sortFrequencies(char values[], float frequencies[], int length);
void reduceFrequencies();

#endif //HUFFMAN_H