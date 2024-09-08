
#ifndef STACKED
#define STACKED

#include <stdio.h>
#include <stdlib.h>

#include "../libs/raylib/raylib.h"
#include "../libs/raylib/raymath.h"
#include "../libs/cebus.h"

typedef struct StackedSprite { 
  char* name;
  Vector2 pos;  
 
  Vector2 dir;  
  f32 vel;
  f32 fricc;
  f32 acc;
  
  f32 radius;
  f32 angle;
  
  const char* sprite_sheet_path;
  i32 num_layers;
  f32 scale;
  f32 y_offset;

  bool steering;
  bool confused;
  f32 cool_down;
   
  // Texture2D texture;
  Texture2D* sprites; 
  
} StackedSprite; 

void load_stacked_sprite(StackedSprite* stacked_sprite){
  Image image = LoadImage(stacked_sprite->sprite_sheet_path);

  stacked_sprite->sprites = (Texture2D*) malloc(sizeof(Texture2D) * stacked_sprite->num_layers);  
  i32 patches_sizes = image.height / stacked_sprite->num_layers;     
  for(i32 i = 0; i < stacked_sprite->num_layers; i++){
    Image temp = ImageFromImage(image, (Rectangle){0,(f32)patches_sizes*i,(f32)image.width,(f32)patches_sizes});
    stacked_sprite->sprites[i] = LoadTextureFromImage(temp);
  }

  stacked_sprite->angle = 0.0f;
  stacked_sprite->vel   = 0.0f;
  stacked_sprite->fricc = -0.02f;
  stacked_sprite->acc   = 0.0f;

  stacked_sprite->radius = 10; 
  stacked_sprite->steering = false;
  
  stacked_sprite->confused = false;
  stacked_sprite->cool_down = 1.0f;

  stacked_sprite->dir = Vector2Rotate((Vector2){stacked_sprite->radius, 0.0f}, stacked_sprite->angle * DEG2RAD); 
}

void update_player_stacked_sprite(StackedSprite* player){
  
  if(player->confused){
    if(player->cool_down >= 0.0f) { 
      player->cool_down -= GetFrameTime();  
      player->angle += 0.2f;
    }
    else { 
      player->confused = false;
      player->cool_down = 1.0f;
    }
  }

  if(IsKeyDown(KEY_RIGHT) && !player->confused) {    
    player->angle += 1.0f;
    player->steering = true;
  }
  if(IsKeyDown(KEY_LEFT) && !player->confused) {    
    player->angle -= 1.0f;
    player->steering = true;
  } 
  
  player->dir = Vector2Rotate((Vector2){player->radius, 0.0f}, player->angle * DEG2RAD);   
  if(player->vel > 5.0f) player->vel = 5.0f;
 
  if (IsKeyDown(KEY_SPACE) && !player->confused) {
    player->acc = 0.1f;
    player->vel += player->acc; 
  } 
 if(player->confused){
    player->acc = -2.0f;
    player->vel += player->acc;
  }
  
  player->pos = Vector2Add(player->pos, Vector2Scale(Vector2Normalize(player->dir), player->vel));   
  
  player->vel += player->fricc;
  if(player->vel <= 0.0001f) player->vel = 0.0f; 
}

void draw_stacked_sprite(StackedSprite* stacked_sprite){ 

  // Object Position
  f32 posX = stacked_sprite->pos.x;
  f32 posY = stacked_sprite->pos.y;

  // Just drawing
  Rectangle sourceRec = { 0.0f, 0.0f, (f32)stacked_sprite->sprites[0].width, (f32)stacked_sprite->sprites[0].height };
  Vector2 rot_center  = {stacked_sprite->sprites[0].width * 0.5f, stacked_sprite->sprites[0].height * 0.5f};

  // Collision Center
  Vector2 center = Vector2Rotate((Vector2){posX, posY + stacked_sprite->y_offset}, 0);
   
  for(i32 i = stacked_sprite->num_layers-1; i >= 0; i--){
    f32 updated_posY = posY + i*stacked_sprite->scale;
    Rectangle destRec = { posX, updated_posY, (f32)stacked_sprite->sprites[0].width, (f32)stacked_sprite->sprites[0].height }; 
    DrawTexturePro(stacked_sprite->sprites[i], sourceRec, destRec, rot_center, stacked_sprite->angle, WHITE);
  }

  // DrawCircleV(center, stacked_sprite->radius, GREEN);   
  // DrawLineEx(center, Vector2Add(center, stacked_sprite->dir), 5, RED);
}

#endif // !STACKED


