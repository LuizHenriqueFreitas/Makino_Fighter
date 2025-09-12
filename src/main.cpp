#include "raylib.h"
#include <iostream>
#include "MAKINO.H"
#include <enemyManager.cpp>

Makino makino;

int main() 
{
    //definindo tamanho da janela e frequencia do gameloop
    const int screen_width = 1280;
    const int screen_heigth = 800;
    InitWindow(screen_width, screen_heigth, "Makino Figther");
    SetTargetFPS(60);

    //carregando sprites
    Texture2D makinoStop = LoadTexture("makinoParado.png");
    if(makinoStop.id == 0)
    {
        std::cout << "erro ao carregar makino.png";
    }
    Texture2D makinoJab = LoadTexture("makinoJab.png");
    if(makinoJab.id == 0)
    {
        std::cout << "erro ao carregar makino.png";
    }

    EnemyManager manager(50);
    manager.SpawnEnemies(10, screen_width, screen_heigth);

    //iniciando makino
    makino.Init(makinoStop, screen_width / 2, screen_heigth / 2);

    while(WindowShouldClose() == false)
    {
        Vector2 makinoPos = {makino.x, makino.y};
        makino.Update(makinoStop, makinoJab);
        manager.UpdateALL(makinoPos);

        BeginDrawing();

        ClearBackground(RAYWHITE);
        makino.Draw();
        manager.DrawALL();

        EndDrawing();
    }

    UnloadTexture(makinoStop);
    CloseWindow();
    return 0;
}