#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"
#define VELIKOST_TEXTU 50
#define MAX_POCET_CISLIC 5
#define VYCHOZI_CAS 10

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

    InitAudioDevice();
    Sound jeKonec = LoadSound("JE KONEC.mp3");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        int key = GetCharPressed();
        while (key > 0) {
            if ((key >= 48) && (key <= 57) && (pocetCislic < MAX_POCET_CISLIC) && !timer) {
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
        if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER) && !timer && pocetCislic != 0) {
            float sekund = atof(cisliceSekundPtr);
            if (sekund != 0) {
                currentTime = GetTime();
                endTime = currentTime + sekund;
                pocetCislic = 0;
                timer = true;
            }
            FILE *file;
            file = fopen("cislo.txt", "w");
            fprintf(file, cisliceSekundPtr);
            fclose(file);
        } else if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER)) {
            memset(cisliceSekund, 0, MAX_POCET_CISLIC);
            timer = false;
        }
        if (IsKeyPressed(KEY_SPACE)) {
            float sekund = 0;
            FILE *file;
            file = fopen("cislo.txt", "r");
            if (file == NULL) {
                printf("Soubor cislo.txt neexistuje, výchozí čas je %d sekund.\n", VYCHOZI_CAS);
                sekund = VYCHOZI_CAS;
            } else {
                fscanf(file, "%f", &sekund);
                fclose(file);
            }
            currentTime = GetTime();
            if (sekund <= 0) {
                printf("Soubor cislo.txt je rozbitý, výchozí čas je %d sekund.\n", VYCHOZI_CAS);
                sekund = VYCHOZI_CAS;
            }
            endTime = currentTime + sekund;
            pocetCislic = 0;
            timer = true;
        }
        BeginDrawing();
            ClearBackground(GRAY);
            if (timer) {
                currentTime = GetTime();
                float remainingTime = endTime - currentTime;
                float setTime = remainingTime;
                if (remainingTime <= 0) {
                    timer = false;
                    PlaySound(jeKonec);
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
