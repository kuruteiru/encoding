#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman/huffman.h"
#include "shannon-fano/shannon_fano.h"

#ifndef RAYGUI_IMPLEMENTATION
#define RAYGUI_IMPLEMENTATION

#include "raylib.h"
#include "raygui.h"

uint32_t floatToString(char *str, uint32_t size, float number, uint32_t precision);

void processInput(char input[], char *valuesBuffer[], float *frequenciesBuffer[]);
void drawSFTree(SFNode *node, int x, int y, int offsetX, int offsetY);
void drawHuffmanTree(MinHeapNode *node, int x, int y, int offsetX, int offsetY);
void drawSFTable(SFNode *node, int x, int y, int *currentY, int columnWidth, uint8_t codeBuffer[], int depth, int *itemsInColumn);
void drawHuffmanTable(MinHeapNode *node, int x, int y, int *currentY, int columnWidth, uint8_t codeBuffer[], int depth, int *itemsInColumn);

int main() {
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
            DrawText("average code length: ", 150, 25, 20, BLACK);
            float averageCodeLength = getAverageHuffmanCodeLength(huffmanTree);
            uint32_t size = floatToString(NULL, 0, averageCodeLength, 2) + 1;
            char averageCodeLengthStr[size];
            floatToString(averageCodeLengthStr, size, averageCodeLength, 2);
            DrawText(averageCodeLengthStr, 400, 25, 20, BLACK);

            DrawText("encoding effectivity: ", 150, 50, 20, BLACK);
            float codeEffectivity = getHuffmanCodeEffectivity(huffmanTree);
            size = floatToString(NULL, 0, codeEffectivity, 2) + 1;
            char codeEffectivityStr[size];
            floatToString(codeEffectivityStr, size, codeEffectivity, 2);
            DrawText(codeEffectivityStr, 400, 50, 20, BLACK);

            int startX = 150;
            int startY = 100;
            int currentY = startY;
            int columnWidth = 75;
            int itemsInColumn = 0;
            uint8_t codeBuffer[256];

            drawHuffmanTable(huffmanTree, startX, startY, &currentY, columnWidth, codeBuffer, 0, &itemsInColumn);
            drawHuffmanTree(huffmanTree, screenWidth / 2, 450, 450, 75);
        } else if (drawShannonFano) {
            // float averageCodeLength = getAverageSFCodeLength(shannonFanoTree);
            // uint32_t size = floatToString(NULL, 0, averageCodeLength, 2) + 1;
            // char averageCodeLengthStr[size];
            // floatToString(averageCodeLengthStr, size, averageCodeLength, 2);
            // GuiLabel((Rectangle){screenWidth / 2 - 100, screenHeight - 100, 300, 20}, averageCodeLengthStr);
            //
            // float codeEffectivity = getSFCodeEffectivity(shannonFanoTree);
            // size = floatToString(NULL, 0, codeEffectivity, 2) + 1;
            // char codeEffectivityStr[size];
            // floatToString(codeEffectivityStr, size, codeEffectivity, 2);
            // GuiLabel((Rectangle){screenWidth / 2 + 100, screenHeight - 100, 300, 20}, codeEffectivityStr);
            //     
            // drawSFTree(shannonFanoTree, screenWidth / 2, 40, 400, 50);

            DrawText("average code length: ", 150, 25, 20, BLACK);
            float averageCodeLength = getAverageSFCodeLength(shannonFanoTree);
            uint32_t size = floatToString(NULL, 0, averageCodeLength, 2) + 1;
            char averageCodeLengthStr[size];
            floatToString(averageCodeLengthStr, size, averageCodeLength, 2);
            DrawText(averageCodeLengthStr, 400, 25, 20, BLACK);

            DrawText("encoding effectivity: ", 150, 50, 20, BLACK);
            float codeEffectivity = getSFCodeEffectivity(shannonFanoTree);
            size = floatToString(NULL, 0, codeEffectivity, 2) + 1;
            char codeEffectivityStr[size];
            floatToString(codeEffectivityStr, size, codeEffectivity, 2);
            DrawText(codeEffectivityStr, 400, 50, 20, BLACK);

            int startX = 150;
            int startY = 100;
            int currentY = startY;
            int columnWidth = 75;
            int itemsInColumn = 0;
            uint8_t codeBuffer[256];

            drawSFTable(shannonFanoTree, startX, startY, &currentY, columnWidth, codeBuffer, 0, &itemsInColumn);
            drawSFTree(shannonFanoTree, screenWidth / 2, 450, 450, 75);
        }

        if (!drawMenu) {
            if (GuiButton((Rectangle){ 20, 20, 80, 50 }, "back")) {
                drawShannonFano = false;
                drawHuffman = false;
                drawMenu = true;
            } 

            EndDrawing();
            continue;
        }

        GuiLabel((Rectangle){screenWidth / 2 - 150, 130, 300, 20}, "input string to encode");

        if (GuiTextBox((Rectangle){ screenWidth / 2 - 150, 150, 300, 50 }, inputBuffer, 256, editMode)) {
            editMode = !editMode;
        }

        GuiLabel((Rectangle){screenWidth / 2 - 150, 220, 300, 20}, "select encoding method");

        if (GuiButton((Rectangle){ screenWidth / 2 - 150, 240, 300, 50 }, "huffman")
            && strlen(inputBuffer)) {
            drawHuffman = true;
            drawMenu = false;

            processInput(inputBuffer, &values, &frequencies);
            huffmanTree = buildHuffmanTree(values, frequencies, strlen(values));

            // printf("inputBuffer: %s\n", inputBuffer);
            // printf("huffman:\n");
            // huffmanEncode(values, frequencies, strlen(values));
            // printf("\n");
        } 

        if (GuiButton((Rectangle){ screenWidth / 2 - 150, 300, 300, 50 }, "shannon-fano")
            && strlen(inputBuffer)) {
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

uint32_t floatToString(char *str, uint32_t size, float number, uint32_t precision) {
    return snprintf(str, size, "%.*f", precision, number);
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
        DrawText("0", x - offsetX - labelWidth / 2, y + offsetY - rectHeight - 10, 20, RED);
        drawSFTree(node->left, x - offsetX, y + offsetY, offsetX / 2, offsetY);
    }

    if (node->right) {
        DrawLine(x, lineY, x + offsetX, y + offsetY, DARKGRAY);
        int labelWidth = MeasureText("1", 20);
        DrawText("1", x + offsetX - labelWidth / 2, y + offsetY - rectHeight - 10, 20, RED);
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
        DrawText("0", x - offsetX - labelWidth / 2, y + offsetY - rectHeight - 10, 20, BLUE);
        drawHuffmanTree(node->left, x - offsetX, y + offsetY, offsetX / 2, offsetY);
    }

    if (node->right) {
        DrawLine(x, lineY, x + offsetX, y + offsetY, DARKGRAY);
        int labelWidth = MeasureText("1", 20);
        DrawText("1", x + offsetX - labelWidth / 2, y + offsetY - rectHeight - 10, 20, BLUE);
        drawHuffmanTree(node->right, x + offsetX, y + offsetY, offsetX / 2, offsetY);
    }
}

void drawSFTable(SFNode *node, int x, int y, int *currentY, int columnWidth, uint8_t codeBuffer[], int depth, int *itemsInColumn) {
    if (!node) return;

    if (node->left) {
        codeBuffer[depth] = 0;
        drawSFTable(node->left, x, y, currentY, columnWidth, codeBuffer, depth + 1, itemsInColumn);
    }

    if (node->right) {
        codeBuffer[depth] = 1;
        drawSFTable(node->right, x, y, currentY, columnWidth, codeBuffer, depth + 1, itemsInColumn);
    }

    if (isSFNodeLeaf(node)) {
        if (*itemsInColumn % 10 == 0) {
            *currentY = y;
        }

        x += (*itemsInColumn / 10) * (columnWidth * 3);

        DrawText(node->value, x, *currentY, 20, BLACK);

        char code[256];
        for (int i = 0; i < depth; i++) {
            code[i] = codeBuffer[i] + '0';
        }
        code[depth] = '\0';

        DrawText(code, x + columnWidth, *currentY, 20, BLACK);

        *currentY += 25;
        (*itemsInColumn)++;
    }
}

void drawHuffmanTable(MinHeapNode *node, int x, int y, int *currentY, int columnWidth, uint8_t codeBuffer[], int depth, int *itemsInColumn) {
    if (!node) return;

    if (node->left) {
        codeBuffer[depth] = 0;
        drawHuffmanTable(node->left, x, y, currentY, columnWidth, codeBuffer, depth + 1, itemsInColumn);
    }

    if (node->right) {
        codeBuffer[depth] = 1;
        drawHuffmanTable(node->right, x, y, currentY, columnWidth, codeBuffer, depth + 1, itemsInColumn);
    }

    if (isLeaf(node)) {
        if (*itemsInColumn % 10 == 0) {
            *currentY = y;
        }

        x += (*itemsInColumn / 10) * (columnWidth * 3);

        DrawText(TextFormat("%c", node->value), x, *currentY, 20, BLACK);

        char code[256];
        for (int i = 0; i < depth; i++) {
            code[i] = codeBuffer[i] + '0';
        }
        code[depth] = '\0';

        DrawText(code, x + columnWidth, *currentY, 20, BLACK);

        *currentY += 25;
        (*itemsInColumn)++;
    }
}

#endif //RAYGUI_IMPLEMENTATION
