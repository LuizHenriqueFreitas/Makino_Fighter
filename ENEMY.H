#ifndef __ENEMY_H
#define __ENEMY_H

#include <string>
#include "raylib.h"
#include <cmath>

void Attack(float dist,Rectangle *src)
{
    if(dist <= 10)
        *src = {32, 0, 32, 32};
    else *src = {0, 0, 32, 32};
}


class Enemy{
    public:
        Vector2 pos;
        int life;
        float speed = 2;
        float rotation;
        bool active = false;
        Texture2D enemySprite;
        Rectangle src;

        Enemy() 
        {
            pos = { 0, 0 };
            speed = 0;
            active = false;
        }

        //controle de animação(que ainda nao vai ter)
        /*
        int spriteSize = 32;
        int currentFrame = 0;
        int maxFrames = 2;
        */

        void Spawn(int screenWidth, int screenHeight, Texture2D spriteSheet)
        {
            int side = rand() % 4;
            speed = 2 + rand() % 3;
            life = 1 + rand()%3;
            active = true;
            enemySprite = spriteSheet;
            src = {0, 0, 32, 32};

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
            rotation = atan2f(dx, -dy) * (180.0f / PI);

            if (dist > 0) 
            {
                pos.x += (dx / dist) * speed;
                pos.y += (dy / dist) * speed;
            }

            Rectangle *ptr1 = &src;

            Attack(dist, ptr1);

            if(life <= 0 ) active = false;
        }

        void Draw()
        {
            if (active) 
            {

                // origem de rotação no centro do sprite
                Vector2 origin = { enemySprite.width/2, 0 };
                // retângulo destino (aumentando escala)
                Rectangle dest = { pos.x, pos.y, enemySprite.width, enemySprite.height};

                DrawTexturePro(
                    enemySprite,
                    src,
                    dest,
                    origin,
                    rotation,
                    WHITE
                );
            }
        }
};

#endif // __ENEMY_H