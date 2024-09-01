#ifndef SHANNON_FANO_H
#define SHANNON_FANO_H

#include <inttypes.h>
#include <stdbool.h>

typedef struct SFNode {
    struct SFNode *left, *right;
    uint32_t length;
    float frequency;
    char *value;
} SFNode;

SFNode* newSFNode(char value[], float frequency);

bool isSFNodeLeaf(SFNode *node);

SFNode* shannonFanoEncode(char values[], float frequencies[]);
SFNode* buildSFTree(SFNode **nodes, uint32_t start, uint32_t end);

void printSFTree(SFNode *root, int depth, uint8_t codeBuffer[]);
void printSFNodesInline(SFNode **nodes, uint32_t length);

void bubbleSortSFNodes(SFNode **nodes, uint32_t length);
void bubbleSortSFNodesDESC(SFNode **nodes, uint32_t length);

float getAverageSFCodeLength(SFNode *root);
float calculateTotalSFFrequency(SFNode *root);
float calculateSFEntropyRecursive(SFNode *root, float totalFrequency);
float calculateSFEntropy(SFNode *root);
float getSFCodeEffectivity(SFNode *root);

#endif //SHANNON_FANO_H
