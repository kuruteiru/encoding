#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "huffman/huffman.h"
#include "shannon-fano/shannon_fano.h"

int main() {
    char values[] = "cbaedf";
    float frequencies[] = {0.12, 0.09, 0.05, 0.16, 0.13, 0.45};

    SFNode *tree = buildShannonFanoTree(values, frequencies, strlen(values));
    
    // SFNode *node = newSFNode(values, frequencies[0]);
    // SFNode *node2 = newSFNode(NULL, frequencies[0]);

    // if (node) {
    //     printf("value: %s | frequency: %.2f\n", node->value, node->frequency);
    // }
    
    // huffmanEncode(values, frequencies, strlen(values));
    // qsort();

    return 0;
}