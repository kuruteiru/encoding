#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman/huffman.h"
#include "shannon-fano/shannon_fano.h"

#ifndef RAYGUI_IMPLEMENTATION
#define RAYGUI_IMPLEMENTATION

#include "raylib.h"
#include "raygui.h"

void processInput(char input[], char *valuesBuffer[], float *frequenciesBuffer[]);
void drawSFTree(SFNode *node, int x, int y, int offsetX, int offsetY);
void drawHuffmanTree(MinHeapNode *node, int x, int y, int offsetX, int offsetY);

int main() {
    // char values[] = "abcde";
    // float frequencies[] = {0.22, 0.28, 0.15, 0.30, 0.05};

    // printf("values: ");
    // for (size_t i = 0; i < strlen(values); i++) {
    //     printf("%c, ", values[i]);
    // }
    // printf("\n");
    //
    // printf("frequencies: ");
    // for (size_t i = 0; i < sizeof(frequencies) / sizeof(float); i++) {
    //     printf("%.2f, ", frequencies[i]);
    // }

    char *values;
    float *frequencies;

    SFNode *shannonFanoTree = NULL;
    MinHeapNode *huffmanTree = NULL;
    uint8_t codeBuffer[256];

    int screenWidth = 1920;
    int screenHeight = 1080;
    
    // GuiLoadStyle("raygui/style_dark.rgs");
    InitWindow(screenWidth, screenHeight, "encoding");

    bool drawMenu = true;
    bool drawHuffman = false;
    bool drawShannonFano = false;
    bool editMode = false;
    char inputBuffer[256] = "";

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR))); 

        if (drawHuffman) {
            drawHuffmanTree(huffmanTree, screenWidth / 2, 40, 400, 50);
        } else if (drawShannonFano) {
            drawSFTree(shannonFanoTree, screenWidth / 2, 40, 400, 50);
        }

        if (!drawMenu) {
            if (GuiButton((Rectangle){ 20, 20, 80, 50 }, "back")) {
                drawMenu = true;
                drawHuffman = false;
                drawShannonFano = false;
            } 

            EndDrawing();
            continue;
        }

        if (GuiTextBox((Rectangle){ screenWidth / 2 - 150, 150, 300, 50 }, inputBuffer, 256, editMode)) {
            editMode = !editMode;
        }

        if (GuiButton((Rectangle){ screenWidth / 2 - 150, 240, 300, 50 }, "huffman")) {
            drawHuffman = true;
            drawMenu = false;

            processInput(inputBuffer, &values, &frequencies);
            huffmanTree = buildHuffmanTree(values, frequencies, strlen(values));

            // printf("inputBuffer: %s\n", inputBuffer);
            // printf("huffman:\n");
            // huffmanEncode(values, frequencies, strlen(values));
            // printf("\n");
        } 

        if (GuiButton((Rectangle){ screenWidth / 2 - 150, 300, 300, 50 }, "shannon-fano")) {
            drawShannonFano = true;
            drawMenu = false;

            processInput(inputBuffer, &values, &frequencies);
            shannonFanoTree = shannonFanoEncode(values, frequencies);

            // printf("inputBuffer: %s\n", inputBuffer);
            // printf("shannon fano:\n");
            // printSFTree(shannonFanoTree, 0, codeBuffer);
            // printf("\n");
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void processInput(char input[], char *valuesBuffer[], float *frequenciesBuffer[]) {
    uint32_t length = strlen(input);
    uint8_t uniqueCharCount = 0;
    uint8_t charCounter[256] = {0};

    for (size_t i = 0; i < length; i++) {
        if (charCounter[(unsigned char)input[i]] == 0) {
            uniqueCharCount++;
        }
        charCounter[(unsigned char)input[i]]++;
    }

    *frequenciesBuffer = (float*)malloc(uniqueCharCount * sizeof(float));
    *valuesBuffer = (char*)malloc((uniqueCharCount + 1) * sizeof(char));

    uint8_t index = 0;
    for (int i = 0; i < 256; i++) {
        if (charCounter[i] > 0) {
            (*valuesBuffer)[index] = (char)i;
            (*frequenciesBuffer)[index] = (float)charCounter[i] / length;
            index++;
        }
    }
    (*valuesBuffer)[index+1] = '\0';
}

void drawSFTree(SFNode *node, int x, int y, int offsetX, int offsetY) {
    if (!node || !node->value) return;

    int textWidth = MeasureText(node->value, 20);
    int rectWidth = textWidth + 20; 
    int rectHeight = 25;

    DrawRectangle(x - rectWidth / 2, y - rectHeight / 2, rectWidth, rectHeight, RED);
    DrawText(node->value, x - textWidth / 2, y - 10, 20, WHITE);

    int lineY = y + rectHeight / 2;

    if (node->left) {
        DrawLine(x, lineY, x - offsetX, y + offsetY, DARKGRAY);
        int labelWidth = MeasureText("0", 20);
        DrawText("0", x - offsetX - labelWidth / 2, y + offsetY - rectHeight, 20, RED);
        drawSFTree(node->left, x - offsetX, y + offsetY, offsetX / 2, offsetY);
    }

    if (node->right) {
        DrawLine(x, lineY, x + offsetX, y + offsetY, DARKGRAY);
        int labelWidth = MeasureText("1", 20);
        DrawText("1", x + offsetX - labelWidth / 2, y + offsetY - rectHeight, 20, RED);
        drawSFTree(node->right, x + offsetX, y + offsetY, offsetX / 2, offsetY);
    }
}

void drawHuffmanTree(MinHeapNode *node, int x, int y, int offsetX, int offsetY) {
    if (!node || !node->value) return;

    char strValue[2] = {node->value, '\0'};

    int textWidth = MeasureText(strValue, 20);
    int rectWidth = textWidth + 20;
    int rectHeight = 25;

    DrawRectangle(x - rectWidth / 2, y - rectHeight / 2, rectWidth, rectHeight, BLUE);
    DrawText(strValue, x - textWidth / 2, y - 10, 20, WHITE);

    int lineY = y + rectHeight / 2;

    if (node->left) {
        DrawLine(x, lineY, x - offsetX, y + offsetY, DARKGRAY);
        int labelWidth = MeasureText("0", 20);
        DrawText("0", x - offsetX - labelWidth / 2, y + offsetY - rectHeight, 20, BLUE);
        drawHuffmanTree(node->left, x - offsetX, y + offsetY, offsetX / 2, offsetY);
    }

    if (node->right) {
        DrawLine(x, lineY, x + offsetX, y + offsetY, DARKGRAY);
        int labelWidth = MeasureText("1", 20);
        DrawText("1", x + offsetX - labelWidth / 2, y + offsetY - rectHeight, 20, BLUE);
        drawHuffmanTree(node->right, x + offsetX, y + offsetY, offsetX / 2, offsetY);
    }
}

#endif //RAYGUI_IMPLEMENTATION
