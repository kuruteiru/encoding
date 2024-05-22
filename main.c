#include <stdio.h>
#include "huffman/huffman.h"

int main() {
    char values[] = {};
    int frequencies[] = {};
    int size = sizeof(values) / sizeof(values[0]);
    
    huffmanEncode(values, frequencies, size);

    return 0;
}