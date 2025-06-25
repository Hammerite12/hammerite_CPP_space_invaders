#include <raylib.h>
#include "Game.h"
#include <string>

//metoda care va afisa punctele scorului pe ecran
std::string FormatWithLeadingZeros(int number, int width) {
    std::string numberText = std::to_string(number);
    int leadingZeros = width - numberText.length();
    return numberText = std::string(leadingZeros, '0') + numberText;
}

int main()
{
    Color grey = { 29, 29, 27, 255 };
    Color yellow = { 243, 216, 63, 255 };
    int offset = 50;
    int window_width = 750;
    int window_height = 700;

    InitWindow(window_width + offset, window_height + 2 * offset, "C++ Space Invaders");
    InitAudioDevice();

    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);
    Texture2D spaceshipImage = LoadTexture("Graphics/spaceship.png");

    SetTargetFPS(60);

    Game game;
    
    while(WindowShouldClose() == false) {       //fereastra va rula jocul atata timp cat utilizatorul nu va apasa pe Esc sau pe X
        UpdateMusicStream(game.music);
        game.HandleInput();
        game.Update();
        BeginDrawing();                                                             //functia care creaza fundalul negru al jocului
        ClearBackground(grey);                                                      //functia care inlocuieste fundalul negru cu un fundal gri
        DrawRectangleRoundedLinesEx({ 10, 10, 780, 780 }, 0.18, 20, 2, yellow);     //functia care creaza marginea jocului
        DrawLineEx({ 25, 730 }, { 775, 730 }, 3, yellow);                           //functia care separa elementele jocului de tabela scorului

        if (game.run) {
            DrawTextEx(font, "LEVEL 01", { 570, 740 }, 34, 2, yellow);
        }
        else {
            DrawTextEx(font, "GAME OVER", { 570, 740 }, 34, 2, yellow);
        }

        float x = 50.0;
        for (int i = 0; i < game.lives; i++) {
            DrawTextureV(spaceshipImage, { x, 745 }, WHITE);
            x += 50;
        }

        DrawTextEx(font, "SCORE", { 50, 15 }, 34, 2, yellow);
        std::string scoreText = FormatWithLeadingZeros(game.score, 5);
        DrawTextEx(font, scoreText.c_str(), { 50, 40 }, 34, 2, yellow);

        DrawTextEx(font, "HIGH-SCORE", { 570, 15 }, 34, 2, yellow);
        std::string highscoreText = FormatWithLeadingZeros(game.highscore, 5);
        DrawTextEx(font, highscoreText.c_str(), { 655, 40 }, 34, 2, yellow);

        game.Draw();
        EndDrawing();                                                               //functia care opreste crearea fundalului negru
    }

    CloseWindow();
    CloseAudioDevice();
}
