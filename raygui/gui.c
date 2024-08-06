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
