#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "shannon_fano.h"

SFNode* newSFNode(char value[], float frequency) {
    SFNode *node = (SFNode*)malloc(sizeof(SFNode));
    if (!node) return NULL;
    
    node->left = NULL;
    node->right = NULL;
    node->code = NULL;
    node->length = !value ? 0 : strlen(value);
    node->frequency = frequency;
    node->value = value;

    return node;
}

bool isSFNodeLeaf(SFNode *node) {
    if (!node) return false;
    return !node->left && !node->right;
}

SFNode** splitSFNode(SFNode *node) {
    if (!node) return NULL;
}

float sumFloatArray(float array[], uint32_t length) {
    if (!array) return 0;
    float sum = 0;
    for (size_t i = 0; i < length; i++) {
        sum += array[i];
    }
    return sum; 
}

// SFNode* buildShannonFanoTree(char values[], float frequencies[]) {
//     if (!values || !frequencies) return NULL;

//     uint32_t length = strlen(values);
//     SFNode *root = newSFNode(values, sumFloatArray(frequencies, strlen(values)));
//     // SFNode *current = root;

//     float left[length];
//     // float right[] = frequencies;
//     for (size_t i = 0; i < length; i++) {
//         left[i] = frequencies[i];
//         float leftSum = sumFloatArray(left, i+1);
//         float rightSum = sumFloatArray(&frequencies[i + 1], length - (i + 1));
//         printf("leftsum: %.3f, rightsum: %.3f\n", leftSum, rightSum);
//         if (leftSum > rightSum) {
//             printf("found\n");
//         }
//     }

//     return root;
// }

// SFNode* buildShannonFanoTree(SFNode *parent, uint32_t length, char *values, float *frequencies) {
//     if (!values || !frequencies) return NULL;

//     char leftValues[length];
//     float leftFrequency = 0;

//     char rightValues[length];
//     strcpy(rightValues, values);
//     float rightFrequency = sumFloatArray(frequencies, length);

//     uint32_t i = 0;
//     for (i = 0; i < length; i++) {
//         if (leftFrequency < rightFrequency) {
//             printf("found\n");
//             leftValues[i] = values[i];
//         }
//         leftFrequency += frequencies[i];
//         rightFrequency -= frequencies[i];
        
//         printf("leftsum: %.3f, rightsum: %.3f\n", leftFrequency, rightFrequency);

//     }

//     SFNode *left = newSFNode(leftValues, leftFrequency);
//     SFNode *right = newSFNode(rightValues, rightFrequency);

//     left = buildShannonFanoTree(parent->left, i, values, frequencies);
//     right = buildShannonFanoTree(parent->right, length - i, values[i], frequencies);

//     if (left) parent->left = left;
//     if (right) parent->right = right;

//     return parent;
// }

SFNode* buildShannonFanoTree(char *values, float *frequencies, uint32_t length) {
    if (!values || !frequencies) return NULL;

    SFNode **nodes = (SFNode**)malloc(length * sizeof(SFNode*));

    for (size_t i = 0; i < length; i++) {
        nodes[i] = newSFNode(&values[i], frequencies[i]);
    }
    
    SFNode *root = buildTree(nodes, 0, length);

    return root;
}

SFNode* buildTree(SFNode **nodes, uint32_t start, uint32_t end) {
    SFNode *current = nodes[start];
    if (start >= end) current;

    float totalFrequency = 0;
    for (size_t i = start; i < end; i++) {
        totalFrequency += nodes[i]->frequency;
    }
    
    uint32_t mid;
    float midFrequency = 0;
    for (uint32_t i = start; i < end; i++) {
        midFrequency += nodes[i]->frequency;
        if (midFrequency >= totalFrequency / 2) {
            mid = i;
            break;
        }
    }

    SFNode *left = buildTree(nodes, start, mid);
    SFNode *right = buildTree(nodes, mid + 1, end);

    current->left = left; 
    current->right = right; 

    return current;
}

// void appendSFNode(SFNode *parent, SFNode *node) {
//     if (!parent) return;

//     if (!parent->left) {
//         parent->left = node;
//         return;
//     }
    
//     if (!parent->right) {
//         parent->right = node;
//         return;
//     }
// }