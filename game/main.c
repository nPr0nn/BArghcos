
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

#include "game.c"

int main(void) {
  // Initialization
  //--------------------------------------------------------------------------------------
  const int screenWidth = 1280;
  const int screenHeight = 720;

  SetTraceLogLevel(LOG_NONE);
  SetConfigFlags(FLAG_MSAA_4X_HINT);
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);

  InitWindow(screenWidth, screenHeight, "Livreeeee");
  SetTargetFPS(60); // Set our game to run at 60 frames-per-second
 
  Context game;
  game_init(&game);
  core_loop(&game, game_loop);
  game_exit(&game);
  
  CloseWindow();
  return 0;
}
