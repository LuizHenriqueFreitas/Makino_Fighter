#ifndef __MAKINO_H
#define __MAKINO_H

#include "raylib.h"
#include <string>
#include <cmath>

// ---------------- MOVIMENTO ----------------
//verifica movimentação do player nos eixos verticais
void VerticalMoveSensor(float *v,float *speed)
{
    if(IsKeyDown(KEY_S))
    {
        *v = *v + *speed;
    } else if(IsKeyDown(KEY_W))
    {
        *v = *v - *speed;
    }
}

//verifica movimentação do plauer nos eixos horizontais + veticais
void MoveSensor(float *h, float *v, float *speed_X, float *speed_Y)
{
    VerticalMoveSensor(v, speed_Y);
    if(IsKeyDown(KEY_A))
    {
        *h = *h - *speed_X;
        VerticalMoveSensor(v, speed_Y);
    }else if(IsKeyDown(KEY_D))
    {
        *h = *h + *speed_X;
        VerticalMoveSensor(v, speed_Y);
    }
}

// ---------------- ATAQUES ----------------
// Define a linha da spritesheet (row) dependendo da ação
int AttackSensor()
{
    //caso MouseLeftButton seja pressioado
    if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))//sprite de jab
        return 1;
    else if(IsMouseButtonDown(MOUSE_RIGHT_BUTTON))//sprite de direto
        return 2;
    else if(IsKeyDown(KEY_SPACE))//sprite de bloqueio
        return 3;
    //caso nada seja pressionado volta ao sprite normal
    return 0;
}

// ---------------- CLASSE MAKINO ----------------
class Makino
{
    public:
        float x, y; //posição do player no canvas
        float moveSpeed_X = 5, moveSpeed_Y = 3; //velocidade de movimento do player
        float rotation; //rotação do player
        float scale = 1.3; //escala do player
        float originAligne_Y = -10; //parametro para alinhamento do sprite verticalmente
        
        float* ptrScale = &scale; //ponteiro para manuzeio da escala do player
        float* ptrOriginAligne_Y = &originAligne_Y; //ponteiro para manuzeio do parametro de alinhamento vertical do sprite

        Texture2D makinoSprite; //slot de sprite do player

        //Controle de animação
        int spriteSize = 32; //cada sprite tem 32x32 pixel
        int currentRow = 0; //referente a linha atual (idle=0, ataque = 1,2,3 etc)
        int currentFrame = 0; //coluna atual
        int maxFrames = 4; //nº de colunas por linha

        float frameTime = 0.08f; //tempo entre frames
        float frameCounter = 0; //acumula tempo

        Rectangle src = {0, 0, 32, 32};

        void Init(Texture2D texture, float startX, float startY) //inicia o player com as configurações iniciais padrão
        {
            makinoSprite = texture;
            x = startX;
            y = startY;
        }
        
        //trás os sprites por referencia para serem trocados quando necessario
        void Update(Texture2D makinoSpriteSheet)
        {
            //mapeando movimentos do player e mouse
            Vector2 makinoPos = { x, y};
            Vector2 mousePos = GetMousePosition();

            //calculando a diferença de distancia entre player e mouse
            float dx = mousePos.x - makinoPos.x;
            float dy = mousePos.y - makinoPos.y;
            //calculando os graus de rotação com base na posição do mouse em relação ao player
            rotation = atan2f(dx, -dy) * (180.0f / PI);

            //dash ao pressionar leftShift
            if(IsKeyDown(KEY_LEFT_SHIFT)){
                moveSpeed_X = 8;
                moveSpeed_Y = 6;
            }else{
                moveSpeed_X = 5;
                moveSpeed_Y = 2;
            }

            //seleciona a linha da spritesheet
            currentRow = AttackSensor();
            //atualiza animação
            frameCounter += GetFrameTime();
            if(frameCounter >= frameTime)
            {
                frameCounter = 0;
                currentFrame++;
                if(currentFrame >= maxFrames) currentFrame = 0;
            }
            //atualiza recorte da spritesheet
            src = {
                (float)(currentFrame * spriteSize),
                (float)(currentRow * spriteSize),
                (float)spriteSize,
                (float)spriteSize
            };

            //verifica movimentação do personagem
            MoveSensor(&x, &y, &moveSpeed_X, &moveSpeed_Y);
        }

        void Draw()
        {
            
            // origem de rotação no centro do sprite
            Vector2 origin = { makinoSprite.width/2, -originAligne_Y };
            // retângulo destino (aumentando escala)
            Rectangle dest = { x, y, makinoSprite.width * scale, makinoSprite.height * scale };
            

            DrawTexturePro(
                makinoSprite, 
                src, 
                dest, 
                origin,   // pivô no centro
                rotation, // ângulo
                WHITE
            );
        }
};

#endif // __MAKINO.H