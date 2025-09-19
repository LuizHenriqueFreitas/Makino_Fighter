#include <iostream>
#include "raylib.h"
#include "MAKINO.H"
#include "EnemyManager.h"

Makino makino;

int main() 
{
    //definindo tamanho da janela e frequencia do gameloop
    const int screen_width = 1280;
    const int screen_heigth = 800;
    InitWindow(screen_width, screen_heigth, "Makino Figther");
    SetTargetFPS(60);

    //carregando sprites
    Texture2D makinoSprites = LoadTexture("makino_SpriteSheet.png");
    if(makinoSprites.id == 0)
    {
        std::cout << "erro ao carregar makino.png";
    }
    Texture2D enemySprites = LoadTexture("inimigos makino.png");
    if(makinoSprites.id == 0)
    {
        std::cout << "erro ao carregar inimigos-makino.png";
    }

    EnemyManager manager(10);
    manager.SpawnEnemies(enemySprites, 10, screen_width, screen_heigth);

    //iniciando makino
    makino.Init(makinoSprites, screen_width / 2, screen_heigth / 2);

    while(WindowShouldClose() == false)
    {
        //atualiza posição do makino em tempo real
        Vector2 makinoPos = {makino.x, makino.y};

        makino.Update(makinoSprites);
        manager.UpdateALL(makinoPos);

        BeginDrawing();

        ClearBackground(RAYWHITE);
        makino.Draw();
        manager.DrawALL();

        EndDrawing();
    }

    UnloadTexture(makinoSprites);
    CloseWindow();
    return 0;
}