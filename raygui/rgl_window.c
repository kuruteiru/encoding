/*******************************************************************************************
*
*   LayoutName v1.0.0 - Tool Description
*
*   LICENSE: Propietary License
*
*   Copyright (c) 2022 raylib technologies. All Rights Reserved.
*
*   Unauthorized copying of this file, via any medium is strictly prohibited
*   This project is proprietary and confidential unless the owner allows
*   usage in any other form by expresely written permission.
*
**********************************************************************************************/

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

//----------------------------------------------------------------------------------
// Controls Functions Declaration
//----------------------------------------------------------------------------------
static void Button002();
static void Button003();

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{
    // Initialization
    //---------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "layout_name");

    // layout_name: controls initialization
    //----------------------------------------------------------------------------------
    bool WindowBox000Active = true;
    bool TextBox004EditMode = false;
    char TextBox004Text[128] = "SAMPLE TEXT";
    //----------------------------------------------------------------------------------

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Implement required update logic
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR))); 

            // raygui: controls drawing
            //----------------------------------------------------------------------------------
            if (WindowBox000Active)
            {
                WindowBox000Active = !GuiWindowBox((Rectangle){ 0, 0, 896, 600 }, "encding");
                GuiPanel((Rectangle){ 300, 120, 300, 100 }, NULL);
                if (GuiTextBox((Rectangle){ 300, 405, 300, 100 }, TextBox004Text, 128, TextBox004EditMode)) TextBox004EditMode = !TextBox004EditMode;
            }
            if (GuiButton((Rectangle){ 300, 290, 300, 50 }, "SAMPLE TEXT")) Button002(); 
            if (GuiButton((Rectangle){ 300, 370, 300, 50 }, "SAMPLE TEXT")) Button003(); 
            //----------------------------------------------------------------------------------

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//------------------------------------------------------------------------------------
// Controls Functions Definitions (local)
//------------------------------------------------------------------------------------
static void Button002()
{
    // TODO: Implement control logic
}
static void Button003()
{
    // TODO: Implement control logic
}

