#ifndef __MAKINO_H
#define __MAKINO_H

#include <string>
#include "raylib.h"
#include <cmath>

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

//verifica se existiram ataques e troca os sprites
//  ATENÇÃO -> inicialmente foram usados sprites separados para cada coisa, mas o recomendado é ter varios sprites compactados num arquivo só, e selecionar as partes desejadas dele
void AttackSensor(Texture2D *Sprite,Texture2D *Stop, Texture2D *Jab, float *scale, float *spriteVerticalAligne)
{
    //caso MouseLeftButton seja pressioado
    if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
        *Sprite = *Jab;
        //revisar isso de aumentar a escala no golpe
        *scale = 5;
        *spriteVerticalAligne = -15;
    }
    //caso nada seja pressionado volta ao sprite normal
    else{
        *Sprite = *Stop;
        *scale = 3;
    }
}

class Makino
{
    public:
        float x, y; //posição do player no canvas
        float moveSpeed_X = 5, moveSpeed_Y = 3; //velocidade de movimento do player
        float rotation; //rotação do player
        float scale = 3; //escala do player
        float originAligne_Y = -32; //parametro para alinhamento do sprite verticalmente
        
        float* ptrScale = &scale; //ponteiro para manuzeio da escala do player
        float* ptrOriginAligne_Y = &originAligne_Y; //ponteiro para manuzeio do parametro de alinhamento vertical do sprite

        Texture2D makinoSprite; //slot de sprite do player

        void Init(Texture2D texture, float startX, float startY) //inicia o player com as configurações iniciais padrão
        {
            makinoSprite = texture;
            x = startX;
            y = startY;
        }
        
        //trás os sprites por referencia para serem trocados quando necessario
        void Update(Texture2D makinoStop, Texture2D makinoJab)
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

            //enviando os sprites para a função de troca
            Texture2D *ptr1 = &makinoSprite; //isso não é um sprite, é o slot onde os sprites se tornam ativos
            Texture2D *ptr2 = &makinoStop; //sprite do player normal
            Texture2D *ptr3 = &makinoJab; //sprite do jab
            AttackSensor(ptr1, ptr2, ptr3, ptrScale, ptrOriginAligne_Y);

            //verifica movimentação do personagem
            MoveSensor(&x, &y, &moveSpeed_X, &moveSpeed_Y);
        }

        void Draw()
        {
            
            // origem de rotação no centro do sprite
            Vector2 origin = { makinoSprite.width+(5.333f*scale), makinoSprite.height-(originAligne_Y*scale) };
            // retângulo destino (aumentando escala)
            Rectangle dest = { x, y, makinoSprite.width * scale, makinoSprite.height * scale };
            // região original do sprite (inteiro)
            Rectangle src = { 0, 0, (float)makinoSprite.width, (float)makinoSprite.height };

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