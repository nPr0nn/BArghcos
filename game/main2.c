
#include "context.h"

#include <stdlib.h>
#include <stdio.h>

typedef void (*void_func_ptr)(void *);
#ifdef PLATFORM_WEB
#include <emscripten.h>
void core_loop(void *ctx, void_func_ptr game_loop) {
  emscripten_set_main_loop_arg(game_loop, ctx, -1, 1);
}
#else
void core_loop(void *ctx, void_func_ptr game_loop) {
  while (!WindowShouldClose()) {
    game_loop(ctx);
  }
}
#endif

void game_init(void* ctx) {
  Context* game = (Context*) ctx;
 
  i32 screenWidth  = GetScreenWidth();
  i32 screenHeight = GetScreenHeight(); 

  game->square_size = 40;
  game->checker_size = 80;

  game->squarePos = (Vector2){screenWidth / 2.0f - game->square_size / 2.0f, screenHeight / 2.0f - game->square_size / 2.0f};
  game->offset = (Vector2){0, 0};

  // Initialize the 2D camera
  game->camera.target = game->squarePos; // Camera target is the player's position
  game->camera.offset = (Vector2){screenWidth / 2.0f, screenHeight / 2.0f}; // Offset to center the player
  game->camera.rotation = 0.0f;
  game->camera.zoom = 1.0f;
}

void game_loop(void* ctx) {
  Context* game = (Context*) ctx;
  
  // Move square and update offset
  if (IsKeyDown(KEY_RIGHT)) { game->squarePos.x += 5.0f;}
  if (IsKeyDown(KEY_LEFT)) { game->squarePos.x -= 5.0f;}
  if (IsKeyDown(KEY_DOWN)) { game->squarePos.y += 5.0f;}
  if (IsKeyDown(KEY_UP)) { game->squarePos.y -= 5.0f;}

  // Update the camera's target to follow the player
  game->camera.target = (Vector2){game->squarePos.x + game->square_size / 2.0f, game->squarePos.y + game->square_size / 2.0f};

  BeginDrawing();
  ClearBackground(RAYWHITE);

  // Begin 2D mode with camera
  BeginMode2D(game->camera);

  i32 screenWidth  = GetScreenWidth();
  i32 screenHeight = GetScreenHeight();

  // Draw the checkerboard pattern
  Vector2 cameraPos = GetScreenToWorld2D((Vector2){0, 0}, game->camera); 
  printf("%f, %f\n", (cameraPos.y/game->checker_size)*game->checker_size, cameraPos.y);
  i32 y_start = (i32) (cameraPos.y / game->checker_size) * game->checker_size - game->checker_size;
  i32 y_end   = cameraPos.y + screenHeight; 
  i32 x_start = (i32) (cameraPos.x / game->checker_size) * game->checker_size - game->checker_size;
  i32 x_end   = cameraPos.x + screenWidth;

  for(i32 y = y_start; y < y_end; y += game->checker_size) {
    for(i32 x = x_start; x < x_end; x += game->checker_size) {
      Color color = (x/game->checker_size + y/game->checker_size) % 2 == 0 ? DARKGRAY : LIGHTGRAY;
      DrawRectangle(x, y, game->checker_size, game->checker_size, color);
    }
  }

  // Draw the green square
  DrawRectangleV(game->squarePos, (Vector2){game->square_size, game->square_size}, GREEN);

  // End 2D mode
  EndMode2D();

  // Draw FPS
  char* fps_str = malloc(sizeof(char) * 32);
  sprintf(fps_str, "FPS: %d", GetFPS());
  DrawText(fps_str, 10, 30, 20, MAROON);
  
  EndDrawing(); 
}

void game_exit(void* ctx) {
  Context* game = (Context*) ctx;
  free(game->array);
}


int main(void) {
  // Initialization
  //--------------------------------------------------------------------------------------
  const int screenWidth = 1280;
  const int screenHeight = 720;

  SetTraceLogLevel(LOG_NONE);
  SetConfigFlags(FLAG_MSAA_4X_HINT);
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);

  InitWindow(screenWidth, screenHeight, "Infinite Grid - Raylib Game Template");
  SetTargetFPS(60); // Set our game to run at 60 frames-per-second
 
  Context game;
  game_init(&game);
  core_loop(&game, game_loop);
  game_exit(&game);
  
  CloseWindow();
  return 0;
}
