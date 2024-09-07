
#include "context.h"
#include "stacked_sprite.h"
#include <stdio.h>

void game_init(void* ctx) {
  Context* game = (Context*) ctx;  

  // Camera 2D 
  // Initialize the 2D camera
  i32 screenWidth  = GetScreenWidth();
  i32 screenHeight = GetScreenHeight();
  game->camera.target = game->squarePos; // Camera target is the player's position
  game->camera.offset = (Vector2){screenWidth / 2.0f, screenHeight / 2.0f}; // Offset to center the player
  game->camera.rotation = 0.0f;
  game->camera.zoom = 5.0f;
  
  // Car init 
  game->car = (StackedSprite){
    .name              = "car",
    .pos               = (Vector2) {0, 0},
    .sprite_sheet_path = "assets/stacked_sprites/car.png",
    .num_layers        = 9,
    .scale             = 2,
    .y_offset          = 10, 
    .angle             = 0,
  };
  load_stacked_sprite(&game->car, false);
  
  game->car.count = 0;
  game->car.state = 0;
}

void game_update(Context* game);
void game_draw(Context* game);

void game_loop(void* ctx){
  Context* game = (Context*) ctx;
  game_update(game);
  game_draw(game);
}

void game_update(Context* game){
  game->car.count += 1;
  if(game->car.count > 50){
    game->car.count = 0;
    game->car.state = (game->car.state + 1) % game->car.num_layers;
  }
  // printf("%d\n", game->car.state);
}

void game_draw(Context* game){
  i32 screenWidth = GetScreenWidth();
  i32 screenHeight = GetScreenHeight();
  
  BeginDrawing();
  ClearBackground((Color){20, 30, 50, 255});
 
  // FPS
  char* fps_str = malloc(sizeof(char) * 32);
  sprintf(fps_str, "FPS: %d", GetFPS());
  printf("%s\n", fps_str);
  DrawText(fps_str, 20, 20, 20, WHITE);
  
  BeginMode2D(game->camera);

  game->car.angle = GetTime() * 10;
  draw_stacked_sprite(&game->car);

  EndMode2D();
  EndDrawing();  
}

void check_events(void* ctx){
 Context* game = (Context*) ctx; 
}

void game_exit(void* ctx){
  Context* game = (Context*) ctx;
  
}
