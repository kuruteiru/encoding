#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman/huffman.h"
#include "shannon-fano/shannon_fano.h"

#ifndef RAYGUI_IMPLEMENTATION
#define RAYGUI_IMPLEMENTATION

#include "raylib.h"
#include "raygui.h"

int gui()
{
    const int windowWidth = 1200;
    const int windowHeight = 600;

    InitWindow(windowWidth, windowHeight, "raygui - controls test suite");
    SetTargetFPS(60);

    bool showMessageBox = false;

    while (!WindowShouldClose())
    {
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

            if (GuiButton((Rectangle){ windowWidth / 2, windowHeight / 2, 400, 100 }, "#191#Show Message")) showMessageBox = true;

            if (showMessageBox)
            {
                int result = GuiMessageBox((Rectangle){ 85, 70, 250, 100 },
                    "#191#Message Box", "Hi! This is a message!", "Nice;Cool");

                if (result >= 0) showMessageBox = false;
            }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

#endif //RAYGUI_IMPLEMENTATION

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

    gui();

    return 0;
}
