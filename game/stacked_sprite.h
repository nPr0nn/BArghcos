
#ifndef STACKED
#define STACKED

#include <stdio.h>
#include <stdlib.h>

#include "../libs/raylib/raylib.h"
#include "../libs/cebus.h"

typedef struct StackedSprite { 
  char* name;
  Vector2 pos;  
  
  const char* sprite_sheet_path;
  i32 num_layers;
  f32 scale;
  f32 y_offset;

  i32 count;
  i32 state;
  f32 angle;
   
  // Texture2D texture;
  Texture2D* sprites; 
  
} StackedSprite; 

void load_stacked_sprite(StackedSprite* stacked_sprite, bool flipped){
  Image image = LoadImage(stacked_sprite->sprite_sheet_path);
  if(flipped) ImageRotateCW(&image);

  stacked_sprite->sprites = (Texture2D*) malloc(sizeof(Texture2D) * stacked_sprite->num_layers);  
  i32 patches_sizes = image.height / stacked_sprite->num_layers;

  for(i32 i = 0; i < stacked_sprite->num_layers; i++){
    Image temp = ImageFromImage(image, (Rectangle){0,(f32)patches_sizes*i,(f32)image.width,(f32)patches_sizes});
    stacked_sprite->sprites[i] = LoadTextureFromImage(temp);
  }   
}

void draw_stacked_sprite(StackedSprite* stacked_sprite){ 
  for(i32 i = stacked_sprite->num_layers-1; i >= 0; i--){
    f32 posX = stacked_sprite->pos.x - stacked_sprite->sprites[i].width * 0.5f;
    f32 posY = stacked_sprite->pos.y - stacked_sprite->sprites[i].height * 0.5f + stacked_sprite->scale * i;
    DrawTextureEx(stacked_sprite->sprites[i], (Vector2){posX, posY}, stacked_sprite->angle, 1.0, WHITE);
  } 
}

#endif // !STACKED

