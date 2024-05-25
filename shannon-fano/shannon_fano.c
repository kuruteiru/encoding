#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "shannon_fano.h"

SFNode* newSFNode(char value[], float frequency) {
    SFNode *node = (SFNode*)malloc(sizeof(SFNode));
    if (!node) return NULL;
    
    node->left = NULL;
    node->right = NULL;
    node->length = !value ? 0 : strlen(value);
    node->frequency = frequency;
    node->value = strdup(value);

    return node;
}

bool isSFNodeLeaf(SFNode *node) {
    if (!node) return false;
    return !node->left && !node->right;
}

int compareSFNodes(const void *nodeA, const void *nodeB) {
    float a = ((SFNode*)nodeA)->frequency;
    float b = ((SFNode*)nodeB)->frequency;
    return (a < b) - (a > b);
}

float sumFloatArray(float array[], uint32_t length) {
    if (!array) return 0;
    float sum = 0;
    for (size_t i = 0; i < length; i++) {
        sum += array[i];
    }
    return sum; 
}

SFNode* shannonFanoEncode(char values[], float frequencies[]) {
    if (!values || !frequencies) return NULL;

    uint32_t length = strlen(values);
    SFNode **nodes = (SFNode**)malloc(length * sizeof(SFNode*));

    for (size_t i = 0; i < length; i++) {
        nodes[i] = newSFNode((char[2]){values[i], '\0'}, frequencies[i]);
    }

    bubbleSortSFNodesDESC(nodes, length);

    SFNode *root = buildSFTree(nodes, 0, length - 1);
    return root;
}

SFNode* buildSFTree(SFNode **nodes, uint32_t start, uint32_t end) {
     if (start >= end) return nodes[start];

    float totalFrequency = 0;
    char totalValue[end - start + 1];
    uint32_t index = 0;
    for (size_t i = start; i <= end; i++) {
        totalFrequency += nodes[i]->frequency;
        totalValue[index++] = *nodes[i]->value;
    }
    totalValue[index] = '\0'; 

    uint32_t mid = start;
    float midFrequency = 0;
    for (uint32_t i = start; i <= end; i++) {
        midFrequency += nodes[i]->frequency;
        if (midFrequency >= totalFrequency / 2) {
            mid = i;
            break;
        }
    }

    SFNode *parent = newSFNode(totalValue, totalFrequency);
    parent->left = buildSFTree(nodes, start, mid); 
    parent->right = buildSFTree(nodes, mid + 1, end); 

    return parent;
}

void printSFTree(SFNode *root, int depth, uint8_t codeBuffer[]) {
    if (!root) return;

    for (int i = 0; i < depth; i++) {
        printf("\t");
    }

    if (root->value && root->value[0] != '\0') {
        printf("[v: %s][f: %.2f][c: ", root->value, root->frequency);
    }

    for (size_t i = 0; i < depth; i++) {
        printf("%d", codeBuffer[i]);
    }

    printf("]\n");

    codeBuffer[depth] = 0;
    printSFTree(root->left, depth + 1, codeBuffer);

    codeBuffer[depth] = 1;
    printSFTree(root->right, depth + 1, codeBuffer);
}

void printSFNodesInline(SFNode **nodes, uint32_t length) {
    for (size_t i = 0; i < length; i++) {
        printf("nodes[%d] v='%s'f=%.2f, ", i, nodes[i]->value, nodes[i]->frequency);
    }
    printf("\n");
}

void bubbleSortSFNodes(SFNode **nodes, uint32_t length) {
    bool swapped;
    for (size_t i = 0; i < length - 1; i++) {
        swapped = false; 
        for (size_t j = 0; j < length - i - 1; j++) {
            if (nodes[j]->frequency < nodes[j + 1]->frequency) continue;
            SFNode *temp = nodes[j];
            nodes[j] = nodes[j + 1];
            nodes[j + 1] = temp;
            swapped = true;
        }
        if (!swapped) break;
    }
}

void bubbleSortSFNodesDESC(SFNode **nodes, uint32_t length) {
    bool swapped;
    for (size_t i = length - 1; i > 0; i--) {
        swapped = false; 
        for (size_t j = length - 1; j > -i - 1 + length; j--) {
            if (nodes[j]->frequency < nodes[j - 1]->frequency) continue;
            SFNode *temp = nodes[j];
            nodes[j] = nodes[j - 1];
            nodes[j - 1] = temp;
            swapped = true;
        }
        if (!swapped) break;
    }
}