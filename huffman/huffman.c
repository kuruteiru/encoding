#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include "huffman.h"

MinHeapNode* newMinHeapNode(char value, float frequency) {
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

MinHeap* newMinHeap(uint32_t capacity) {
    MinHeap *minHeap = (MinHeap*)malloc(sizeof(MinHeap));

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

void minHeapify(MinHeap *self, uint32_t index) {
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
    if (!self) return NULL;
    
    MinHeapNode *min = self->nodes[0];

    self->nodes[0] = self->nodes[self->size - 1];
    self->size--;

    minHeapify(self, 0);

    return min;
}

MinHeap* initializeMinHeap(char values[], float frequencies[], uint32_t capacity) {
    if (!capacity) return NULL;

    MinHeap *minHeap = newMinHeap(capacity);

    minHeap->size = capacity;
    for (uint32_t i = 0; i < capacity; i++) {
        minHeap->nodes[i] = newMinHeapNode(values[i], frequencies[i]);
    }

    minHeapifyNonLeaves(minHeap);

    return minHeap;
}

MinHeapNode* buildHuffmanTree(char values[], float frequencies[], uint32_t capacity) {
    MinHeap *minHeap = initializeMinHeap(values, frequencies, capacity);
    if (!minHeap) return NULL;

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

int getHuffmanTreeHeight(MinHeapNode *node) {
    if (!node) return 0;

    int left = getHuffmanTreeHeight(node->left);
    int right = getHuffmanTreeHeight(node->right);

    if (left > right) return ++left;

    return ++right;
}

void printHuffmanTree(MinHeapNode *node, uint32_t depth, uint8_t codeBuffer[]) {
    if (!node) return;

    if (isLeaf(node)) {
        for (size_t i = 0; i < depth; i++) {
            printf("  ");
        }

        if (node->value && node->frequency) {
            printf("[%c][", node->value, node->frequency);
        }

        for (size_t i = 0; i < depth; i++) {
            printf("%d", codeBuffer[i]);
        }

        printf("]\n");
    } else {
        for (size_t i = 0; i < depth; i++) {
            printf("  ");
        }

        printf("[X]\n");
    } 

    codeBuffer[depth] = 0;
    printHuffmanTree(node->left, depth + 1, codeBuffer);

    codeBuffer[depth] = 1;
    printHuffmanTree(node->right, depth + 1, codeBuffer);

}

void printHuffmanTable(MinHeapNode *node, uint32_t index, uint8_t codeBuffer[]) {
    if (!node) return;

    if (node->left) {
        codeBuffer[index] = 0;
        printHuffmanTable(node->left, index + 1, codeBuffer);
    }
    
    if (node->right) {
        codeBuffer[index] = 1;
        printHuffmanTable(node->right, index + 1, codeBuffer);
    }

    if (isLeaf(node)) {
        printf("v: % c | f: %5.2f | c: ", node->value, node->frequency);
        for (uint32_t i = 0; i < index; i++) {
            printf("%d", codeBuffer[i]);
        }
        printf("\n");
    }
}

void huffmanEncode(char values[], float frequencies[], uint32_t capacity) {
    MinHeapNode *root = buildHuffmanTree(values, frequencies, capacity);
    uint8_t codeBuffer[getHuffmanTreeHeight(root)];
    uint8_t codeBuffer2[getHuffmanTreeHeight(root)];
    uint32_t index = 0;

    // printCodes(root, codeBuffer, index);
    printHuffmanTable(root, index, codeBuffer);
    printHuffmanTree(root, 0, codeBuffer);
    // printHuffmanTree(root, 0, codeBuffer2);
}

void calculateAverageHuffmanCodeLength(MinHeapNode *root, float *totalLength, float *totalFrequency, int currentDepth) {
    if (!root) return;

    if (isLeaf(root)) {
        *totalLength += currentDepth * root->frequency;
        *totalFrequency += root->frequency;
    }

    calculateAverageHuffmanCodeLength(root->left, totalLength, totalFrequency, currentDepth + 1);
    calculateAverageHuffmanCodeLength(root->right, totalLength, totalFrequency, currentDepth + 1);
}

float getAverageHuffmanCodeLength(MinHeapNode *root) {
    float totalLength = 0;
    float totalFrequency = 0;
    calculateAverageHuffmanCodeLength(root, &totalLength, &totalFrequency, 0);
    
    return totalFrequency > 0 ? totalLength / totalFrequency : 0;
}
    
float calculateTotalHuffmanFrequency(MinHeapNode *root) {
    if (root == NULL) return 0;
    if (isLeaf(root)) return root->frequency;
    return calculateTotalHuffmanFrequency(root->left) + calculateTotalHuffmanFrequency(root->right);
}

float calculateHuffmanEntropyRecursive(MinHeapNode *root, float totalFrequency) {
    if (root == NULL) return 0;
    
    if (isLeaf(root)) {
        float probability = root->frequency / totalFrequency;
        return -probability * log2f(probability);
    }
    
    return calculateHuffmanEntropyRecursive(root->left, totalFrequency) + 
           calculateHuffmanEntropyRecursive(root->right, totalFrequency);
}

float calculateHuffmanEntropy(MinHeapNode *root) {
    float totalFrequency = calculateTotalHuffmanFrequency(root);
    return calculateHuffmanEntropyRecursive(root, totalFrequency);
}

float getHuffmanCodeEffectivity(MinHeapNode *root) {
    float averageLength = getAverageHuffmanCodeLength(root);
    float entropy = calculateHuffmanEntropy(root);

    return averageLength > 0 ? entropy / averageLength : 0;
}
