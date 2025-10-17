#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#define VELIKOST_TEXTU 50
#define MAX_POCET_CISLIC 5

const int WIDTH = 800;
const int HEIGHT = 600;

int main() {
    bool timer = false;
    float currentTime;
    float endTime;
    char cisliceSekund[MAX_POCET_CISLIC + 1] = "\0";
    const char *cisliceSekundPtr = cisliceSekund;
    int pocetCislic = 0;
    printf("%f", currentTime);
    InitWindow(WIDTH, HEIGHT, "KV Časovač");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        int key = GetCharPressed();
        while (key > 0) {
            if ((key >= 48) && (key <= 57) && (pocetCislic < MAX_POCET_CISLIC)) {
                cisliceSekund[pocetCislic] = (char)key;
                cisliceSekund[pocetCislic+1] = '\0';
                pocetCislic++;
            }
            key = GetCharPressed();
            
        }
        if (IsKeyPressed(KEY_BACKSPACE)) {
            if (pocetCislic > 0) {
                pocetCislic--;
                cisliceSekund[pocetCislic] = '\0';
            }
        }
        if (IsKeyPressed(KEY_ENTER)) {
            float sekund = atof(cisliceSekundPtr);
            if (sekund != 0) {
                currentTime = GetTime();
                endTime = currentTime + sekund;
                timer = true;
            }
        }
        if (IsKeyPressed(KEY_SPACE)) {
            currentTime = GetTime();
            endTime = currentTime + 10.0;
            timer = true;
        }
        BeginDrawing();
            ClearBackground(GRAY);
            if (timer) {
                currentTime = GetTime();
                float remainingTime = endTime - currentTime;
                if (remainingTime <= 0) {
                    timer = false;
                    continue;
                }
                char buffer[10];
                gcvt(remainingTime, MAX_POCET_CISLIC, buffer);
                DrawText(buffer, WIDTH/2-VELIKOST_TEXTU, HEIGHT/2-VELIKOST_TEXTU, VELIKOST_TEXTU, WHITE);
            } else {
                DrawText(cisliceSekund, WIDTH/2-VELIKOST_TEXTU, HEIGHT/2-VELIKOST_TEXTU, VELIKOST_TEXTU, GREEN);
            }
        EndDrawing();
    }
    return 0;
}
