#ifndef __EnemyManager_H
#define __EnemyManager_H

#include <vector>
#include "raylib.h"
#include "ENEMY.h"

class EnemyManager{
    public:
        std::vector<Enemy> enemies;

        EnemyManager(int maxEnemies)
        {
            enemies.resize(maxEnemies);
        }

        void SpawnEnemies(Texture2D sprites,int count, int screenWidth, int screenHeight)
        {
            for (int i = 0; i < count && i < (int)enemies.size(); i++)
            {
                enemies[i].Spawn(screenWidth, screenHeight, sprites);
            }
            
        }

        void UpdateALL(Vector2 playerPos)
        {
            for(auto &enemy : enemies)
            {
                if (enemy.active) enemy.Update(playerPos);
            }
        }

        void DrawALL() 
        {
            for(auto &enemy : enemies)
            {
                enemy.Draw();
            }
        }
};

#endif //__EnemyManager_H