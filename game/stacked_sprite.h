
#ifndef STACKED
#define STACKED

#include <stdio.h>
#include <stdlib.h>

#include "../libs/raylib/raylib.h"
#include "../libs/raylib/raymath.h"
#include "../libs/cebus.h"

#include "points.h"
#include "collisions.h"

typedef struct StackedSprite { 
  char* name;
  
  i32 lap;
  i32 progress; 
  i32 real_progress; 

  Vector2 pos;  
 
  Vector2 dir;  
  f32 speed;
  Vector2 vel;
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

  Vector2* targets;
  i32 num_targets;
  i32 current_target_index;
   
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

  stacked_sprite->angle = -90;
  stacked_sprite->speed   = 0.0f;
  stacked_sprite->vel     = Vector2Zero();
  stacked_sprite->fricc = 0.982f;
  stacked_sprite->acc   = 0.0f;

  stacked_sprite->radius = 10; 
  stacked_sprite->steering = false;
  
  stacked_sprite->confused = false;
  stacked_sprite->cool_down = 0.3f;

  stacked_sprite->current_target_index = 0;
  
  stacked_sprite->dir = Vector2Rotate((Vector2){stacked_sprite->radius, 0.0f}, stacked_sprite->angle * DEG2RAD); 
}

void create_targets(StackedSprite* stacked_sprite, Point* lines, i32 num_lines){
  stacked_sprite->targets = (Vector2*) malloc(sizeof(Vector2) * 4 * num_lines);
  stacked_sprite->num_targets = 0;
  stacked_sprite->current_target_index = 0;

  for(i32 j = 0; j < 4; j++){ 
    for(i32 i = 0; i < num_lines-1; i += 2){
      stacked_sprite->targets[stacked_sprite->num_targets++] = RandomPointOnLine(lines[i].pos, lines[i+1].pos);
    }
  }
}

#define PS3_NAME_ID         "Sony PLAYSTATION(R)3 Controller"

void update_player(StackedSprite* player){

  // printf("%f %f\n", player->pos.x, player->pos.y);

  if(player->confused){
    player->cool_down -= GetFrameTime();
    if(player->cool_down < 0.0f){
      player->confused = false;
      player->cool_down = 0.3f;
    }
    else{ 
      player->angle += 1.5f;
      player->steering = true;
    }
  }

  if((IsKeyDown(KEY_RIGHT) || IsGamepadButtonDown(0, 12))& !player->confused) {    
    player->angle += 1.5f;
    player->steering = true;
  }
  if((IsKeyDown(KEY_LEFT) || IsGamepadButtonDown(0, 10))& !player->confused) {
    player->angle -= 1.5f;
    player->steering = true;
  }  
  player->dir = Vector2Rotate((Vector2){player->radius, 0.0f}, player->angle * DEG2RAD);   

  if((IsKeyDown(KEY_SPACE) || IsGamepadButtonDown(0, 5) || IsGamepadButtonDown(0, 6) || IsGamepadButtonDown(0, 7) || IsGamepadButtonDown(0, 8) )& !player->confused) {
    player->acc = 32.0f;
    player->speed += player->acc * GetFrameTime(); 
  } 

  if(player->confused){
    player->acc = -80.0f;
    player->speed += player->acc * GetFrameTime();
  };
 
  if(player->speed > 44.0f) player->speed = 44.0f;
  player->speed = player->speed * player->fricc;  

  player->vel = Vector2Scale(player->dir, player->speed);
}

void update_enemy(StackedSprite* enemy){
  
  if(enemy->confused){
    enemy->acc = -80.0f;
    enemy->speed += enemy->acc * GetFrameTime();
  };
 
  if(enemy->confused == false){
   
    enemy->dir = Vector2Normalize(Vector2Subtract(enemy->targets[enemy->current_target_index], enemy->pos));
    enemy->angle = atan2f(enemy->dir.y, enemy->dir.x) * RAD2DEG;

    enemy->acc = GetRandomFloat(200.0f, 350);
    enemy->speed += enemy->acc * GetFrameTime();
    //
    // if(enemy->speed > 84.0f) enemy->speed = 84.0f;
    enemy->speed = enemy->speed * enemy->fricc;
  }

  enemy->vel = Vector2Scale(enemy->dir, enemy->speed);
  
  // enemy->speed += enemy->acc * GetFrameTime();
  // if(enemy->speed > 64.0f) enemy->speed = 64.0f;
  // enemy->speed = enemy->speed * enemy->fricc;
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
  
  // DrawCircleV(center, 10, WHITE);

  for(i32 i = stacked_sprite->num_layers-1; i >= 0; i--){
    f32 updated_posY = posY + i*stacked_sprite->scale;
    Rectangle destRec = { posX, updated_posY, (f32)stacked_sprite->sprites[0].width, (f32)stacked_sprite->sprites[0].height }; 
    DrawTexturePro(stacked_sprite->sprites[i], sourceRec, destRec, rot_center, stacked_sprite->angle, WHITE);
  }

  // DrawCircleV(center, stacked_sprite->radius, GREEN);   
  // DrawLineEx(center, Vector2Add(center, stacked_sprite->dir), 5, RED);
}

#endif // !STACKED


