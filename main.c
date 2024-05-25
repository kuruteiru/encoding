#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman/huffman.h"
#include "shannon-fano/shannon_fano.h"

int main() {
    // char values[] = "cbaedf";
    // float frequencies[] = {12, 9, 5, 16, 13, 45};

    char values[] = "abcde";
    float frequencies[] = {0.22, 0.28, 0.15, 0.30, 0.05};

    printf("values: ");
    for (size_t i = 0; i < strlen(values); i++) {
        printf("%c, ", values[i]);
    }
    printf("\n");

    printf("frequencies: ");
    for (size_t i = 0; i < sizeof(frequencies) / sizeof(float); i++) {
        printf("%.2f, ", frequencies[i]);
    }
    printf("\n\n");

    printf("huffman:\n");
    huffmanEncode(values, frequencies, strlen(values));
    
    printf("\nshannon fano:\n");
    SFNode *tree = shannonFanoEncode(values, frequencies);
    
    uint8_t codeBuffer[256];
    printSFTree(tree, 0, codeBuffer);

    return 0;
}