#ifndef __ENEMY_H
#define __ENEMY_H

#include <string>
#include <raylib.h>
#include <cmath>

class Enemy{
    public:
        Vector2 pos;
        float speed = 2;
        bool active = false;

        Enemy() 
        {
            pos = { 0, 0 };
            speed = 0;
            active = false;
        }

        void Spawn(int screenWidth, int screenHeight)
        {
            int side = rand() % 4;
            speed = 2+ rand() % 3;
            active = true;

            switch (side)
            {
                case 0: //esquerda
                    pos = {-20.0f, (float) (rand() % screenHeight)};
                    break;
                case 1: //direita
                    pos = {(float)screenWidth + 20, (float)(rand() % screenHeight)};
                    break;
                case 2: //cima
                    pos = {(float)(rand() % screenWidth), -20.0f};
                    break;
                case 3: //baixo
                    pos = {(float)(rand() % screenWidth), (float)screenHeight + 20};
                    break;
            }
        }

        void Update(Vector2 playerPos)
        {
            if (!active) return;

            // direção em direção ao player
            float dx = playerPos.x - pos.x;
            float dy = playerPos.y - pos.y;
            float dist = sqrt(dx*dx + dy*dy);

            if (dist > 0) 
            {
                pos.x += (dx / dist) * speed;
                pos.y += (dy / dist) * speed;
            }
        }

        void Draw()
        {
            if (active) 
            {
                DrawCircleV(pos, 10, RED); // mais tarde troca por textura
            }
        }
};

#endif // __ENEMY_H