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

SFNode* buildShannonFanoTree(char values[], float frequencies[]) {
    if (!values || !frequencies) return NULL;

    uint32_t length = strlen(values);
    SFNode *root = newSFNode(values, sumFloatArray(frequencies, strlen(values)));
    // SFNode *current = root;

    float left[length];
    // float right[] = frequencies;
    for (size_t i = 0; i < length; i++) {
        left[i] = frequencies[i];
        float leftSum = sumFloatArray(left, i+1);
        float rightSum = sumFloatArray(&frequencies[i + 1], length - (i + 1));
        printf("leftsum: %.3f, rightsum: %.3f\n", leftSum, rightSum);
        if (leftSum > rightSum) {
            printf("found\n");
        }
    }

    return root;
}

void appendSFNode(SFNode *parent, SFNode *node) {
    if (!parent) return;

    if (!parent->left) {
        parent->left = node;
        return;
    }
    
    if (!parent->right) {
        parent->right = node;
        return;
    }
}
