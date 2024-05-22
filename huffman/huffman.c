#include <malloc.h>
#include "huffman.h"

MinHeapNode* newMinHeapNode(char value, unsigned int frequency) {
    MinHeapNode *node = (MinHeapNode*)malloc(sizeof(MinHeapNode));

    node->value = value;
    node->frequency = frequency;
    node->left = NULL;
    node->right = NULL;

    return node;
}

void swapMinHeapNodes(MinHeapNode **nodeA, MinHeapNode **nodeB) {
    MinHeapNode *temp = *nodeA;
    *nodeA = *nodeB; 
    *nodeB = temp;
}

bool isLeaf(MinHeapNode *node) {
    if (!node) return false;
    return !node->left && !node->right;
}

MinHeap* newMinHeap(unsigned int capacity) {
    MinHeap *minHeap = (MinHeap*)malloc(sizeof(minHeap));

    minHeap->nodes = (MinHeapNode**)malloc(capacity * sizeof(MinHeapNode*));
    minHeap->capacity = capacity;
    minHeap->size = 0;

    return minHeap;
}

void insertMinHeapNode(MinHeap *self, MinHeapNode *node) {
    if (!self || !node) return;

    self->size++;
    int index = self->size - 1;

    while (index && node->frequency < self->nodes[(index - 1) / 2]->frequency) {
        self->nodes[index] = self->nodes[(index - 1) / 2];
        index = (index - 1) / 2;
    }

    self->nodes[index] = node;
}

void minHeapify(MinHeap *self, unsigned int index) {
    if (!self || index > self->size) return;

    int min = index;
    int left = index * 2 + 1;
    int right = index * 2 + 2;

    if (left < self->size 
    && self->nodes[left]->frequency < self->nodes[min]->frequency) {
        min = left;
    }

    if (right < self->size 
    && self->nodes[right]->frequency < self->nodes[min]->frequency) {
        min = right;
    }

    if (min == index) return;

    swapMinHeapNodes(&self->nodes[min], &self->nodes[index]);
    minHeapify(self, min);
}

void minHeapifyNonLeaves(MinHeap *self) {
    if (!self) return;

    int size = self->size - 1;
    for (int i = (size - 1) / 2; i >= 0; i--) {
        minHeapify(self, i);
    }
}

MinHeapNode* getMinimum(MinHeap *self) {
    if (!self) return;
    
    MinHeapNode *min = self->nodes[0];

    self->nodes[0] = self->nodes[self->size - 1];
    self->size--;
    minHeapify(self, 0);

    return min;
}

MinHeap* initializeMinHeap
(char values[], unsigned int frequencies[], unsigned int capacity) {
    MinHeap *minHeap = newMinHeap(capacity);

    minHeap->size = capacity;
    for (unsigned int i = 0; i < capacity; i++) {
        minHeap->nodes[i] = newMinHeapNode(values[i], frequencies[i]);
    }

    minHeapifyNonLeaves(minHeap);

    return minHeap;
}

MinHeapNode* buildHuffmanTree
(char values[], unsigned int frequencies[], unsigned int capacity) {
    MinHeap *minHeap = initializeMinHeap(values, frequencies, capacity);
    MinHeapNode *left, *right, *parent;

    while (minHeap->size != 1) {
        left = getMinimum(minHeap);
        right = getMinimum(minHeap);

        parent = newMinHeapNode('_', left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;

        insertMinHeapNode(minHeap, parent);
    }
    
    return getMinimum(minHeap);
}

void printIntArray() {

}

void printCodes(MinHeapNode *node, unsigned int codes[], unsigned int index) {
    if (!node) return;
    
    if (node->left) {
        codes[index] = 0;
        printCodes(node->left, codes, index + 1);
    }
    
    if (node->right) {
        codes[index] = 1;
        printCodes(node->right, codes, index + 1);
    }

    if (isLeaf(node)) {
        printf("%d: ", node->value);
        for (unsigned int i = 0; i < index; i++) {
            printf("%d", codes[i]);
        }
        printf("\n");
    }
}