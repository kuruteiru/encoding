#include <stdio.h>
#include "huffman/huffman.h"

int main() {
    char values[] = {'c', 'b', 'a', 'e', 'd', 'f'};
    int frequencies[] = {12, 9, 5, 16, 13, 45};
    int size = sizeof(values) / sizeof(values[0]);
    
    huffmanEncode(values, frequencies, size);

    return 0;
}