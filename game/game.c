
#include "context.h"
#include "stacked_sprite.h"
#include "collisions.h"

#include <stdio.h>

#define EDITOR 1

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif

void game_init(void* ctx) {
  Context* game = (Context*) ctx;  
  i32 screenWidth  = GetScreenWidth();
  i32 screenHeight = GetScreenHeight();

  // Set the dimensions of the screen
  Vector2 screen_dims = (Vector2) { screenWidth, screenHeight };

  // Map
  Image image_map  = LoadImage("assets/maps/track2.png");
  // Image image_map_overlay = LoadImage("assets/maps/track22.png");
  game->map_overlay_offset = (Vector2){-10,-9};
  game->map_top_left       = (Vector2){0,0}; 
  game->map = LoadTextureFromImage(image_map); 
  game->map_overlay = game->map;
  // game->map_overlay = LoadTextureFromImage(image_map_overlay);

  // Ocean Background 
  #ifndef PLATFORM_WEB
  game->bgShader = LoadShader(0, TextFormat("assets/shaders/background.fs", GLSL_VERSION)); 
  #endif
  #ifdef PLATFORM_WEB
  game->bgShader = LoadShader(0, TextFormat("assets/shaders/background_web.fs", GLSL_VERSION)); 
  #endif

  game->timeLoc = GetShaderLocation(game->bgShader, "time");
  game->playerLoc = GetShaderLocation(game->bgShader, "playerPos");  
  i32 resolutionLoc = GetShaderLocation(game->bgShader, "resolution");
  SetShaderValue(game->bgShader, resolutionLoc, &screen_dims, SHADER_UNIFORM_VEC2);

  // Ice Outline
  #ifndef PLATFORM_WEB
  game->iceShader = LoadShader(0, TextFormat("assets/shaders/outline.fs", GLSL_VERSION));
  #endif
  #ifdef PLATFORM_WEB
  game->iceShader = LoadShader(0, TextFormat("assets/shaders/outline_web.fs", GLSL_VERSION));
  #endif

  game->timeLoc2 = GetShaderLocation(game->iceShader, "time"); 
  resolutionLoc = GetShaderLocation(game->iceShader, "resolution");
  SetShaderValue(game->iceShader, resolutionLoc, &screen_dims, SHADER_UNIFORM_VEC2);
  
  // All Ships Settings 
  // ----------------------------------------------------------------------
  // pirateShip
  game->pirateShip = (StackedSprite){
    .name              = "car",
    .pos               = (Vector2) {500, 400},
    .sprite_sheet_path = "assets/ships/pirateShip.png",
    .num_layers        = 15, 
    .scale             = 1.0,
    .y_offset          = 10, 
    .angle             = 0,
  };
  load_stacked_sprite(&game->pirateShip);

  // gamutoShip
  game->gamutoShip = (StackedSprite){
    .name              = "car",
    .pos               = (Vector2) {0, -40},
    .sprite_sheet_path = "assets/ships/gamutoShip.png",
    .num_layers        = 15, 
    .scale             = 1.0,
    .y_offset          = 10, 
    .angle             = 0,
  };
  load_stacked_sprite(&game->gamutoShip);

  // ghostShip
  game->ghostShip = (StackedSprite){
    .name              = "car",
    .pos               = (Vector2) {40, -40},
    .sprite_sheet_path = "assets/ships/ghostShip.png",
    .num_layers        = 15, 
    .scale             = 1,
    .y_offset          = 10, 
    .angle             = 0,
  };
  load_stacked_sprite(&game->ghostShip);

  // jangadaShip
  game->jangadaShip = (StackedSprite){
    .name              = "car",
    .pos               = (Vector2) {80, -40},
    .sprite_sheet_path = "assets/ships/jangadaShip.png",
    .num_layers        = 15, 
    .scale             = 1,
    .y_offset          = 10, 
    .angle             = 0,
  };
  load_stacked_sprite(&game->jangadaShip);

  // merryShip
  game->merryShip = (StackedSprite){
    .name              = "car",
    .pos               = (Vector2) {120, -40},
    .sprite_sheet_path = "assets/ships/merryShip.png",
    .num_layers        = 15, 
    .scale             = 1,
    .y_offset          = 10, 
    .angle             = 0,
  };
  load_stacked_sprite(&game->merryShip);

  // monsterShip
  game->monsterShip = (StackedSprite){
    .name              = "car",
    .pos               = (Vector2) {160, -40},
    .sprite_sheet_path = "assets/ships/monsterShip.png",
    .num_layers        = 12, 
    .scale             = 0.75,
    .y_offset          = 10, 
    .angle             = 0,
  };
  load_stacked_sprite(&game->monsterShip);

  // pinguimShip
  game->pinguimShip = (StackedSprite){
    .name              = "car",
    .pos               = (Vector2) {200, -40},
    .sprite_sheet_path = "assets/ships/pinguimShip.png",
    .num_layers        = 15, 
    .scale             = 1.0,
    .y_offset          = 10, 
    .angle             = 0,
  };
  load_stacked_sprite(&game->pinguimShip); 

   // windowsShip
  game->windowsShip = (StackedSprite){
    .name              = "car",
    .pos               = (Vector2) {240, -40},
    .sprite_sheet_path = "assets/ships/windowsShip.png",
    .num_layers        = 14, 
    .scale             = 1.0,
    .y_offset          = 10, 
    .angle             = 0,
  };
  load_stacked_sprite(&game->windowsShip); 

  //----------------------------------------------------------------------

  game->camera.target = (Vector2){0,0};
  game->camera.offset = (Vector2){screenWidth*0.5f, screenHeight*0.5f - 64}; 
  game->camera.rotation = 0.0f;
  game->camera.zoom = 5.0f;

   // Track Points
  game->collisions = malloc(sizeof(Vector2) * 100);
  i32 new_count = 0;
  // game->collisions = read_points_from_file("colliders.dat", &new_count);
  // printf("read %d collisions\n", new_count);
  game->collisions_count = new_count; 
}

void game_update(Context* game);
void game_draw(Context* game);

void game_loop(void* ctx){
  Context* game = (Context*) ctx;
  game_update(game);
  game_draw(game);
}

void game_update(Context* game){
  i32 screenWidth = GetScreenWidth();
  i32 screenHeight = GetScreenHeight();
  
  f32 time = GetTime() ; 
  SetShaderValue(game->bgShader, game->timeLoc, &time, SHADER_UNIFORM_FLOAT);
  SetShaderValue(game->bgShader, game->playerLoc, &game->pirateShip.pos, SHADER_UNIFORM_VEC2); 
  SetShaderValue(game->iceShader, game->timeLoc2, &time, SHADER_UNIFORM_FLOAT); 
  
  // Move square and update offset

  if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
    Vector2 mouse_pos = (Vector2){GetMouseX(), GetMouseY()};
    Vector2 mouse_pos_world = GetScreenToWorld2D(mouse_pos, game->camera);
    game->collisions[game->collisions_count].pos = mouse_pos_world;
    game->collisions[game->collisions_count].radius = 10.0f;
    game->collisions_count++;
  }
  update_player_stacked_sprite(&game->pirateShip);
 
  for(i32 i = 0; i < game->collisions_count; i++){ 
    f32 posX = game->pirateShip.pos.x;
    f32 posY = game->pirateShip.pos.y + game->pirateShip.y_offset;
    f32 dist = Vector2Distance((Vector2){posX, posY}, game->collisions[i].pos);
    // if(dist <= game->pirateShip.radius + game->collisions[i].radius - 2){
      // game->pirateShip.confused = true;
    // }  
  }
  
  
  game->camera.target = (Vector2){game->pirateShip.pos.x, game->pirateShip.pos.y};  
}


void game_draw(Context* game){
  i32 screenWidth = GetScreenWidth();
  i32 screenHeight = GetScreenHeight();
  
  BeginDrawing();
  ClearBackground((Color){20, 30, 50, 255});
  
  // BeginShaderMode(game->bgShader);
  DrawRectangle(0, 0, screenWidth, screenHeight, WHITE); 
  // EndShaderMode();

  BeginMode2D(game->camera); 

  i32 tintColorLoc = GetShaderLocation(game->iceShader, "tintColor"); 
  float ice_color[4] = {0.47f, 0.815f, 1.0f, 1.0f};
  SetShaderValue(game->iceShader, tintColorLoc, &ice_color, SHADER_UNIFORM_VEC4);
  
  BeginShaderMode(game->iceShader);   
  DrawTextureEx(game->map, (Vector2){0,0}, 0.0f, 2.0f, WHITE);
  EndShaderMode();

  for(i32 i = 0; i < game->collisions_count; i++){
    DrawCircleV(game->collisions[i].pos, game->collisions[i].radius, RED);
  }
  for(i32 i = 0; i < game->collisions_count-1; i++){
    DrawLineEx(game->collisions[i].pos, game->collisions[i+1].pos, 2, GREEN);
  }
  
  draw_stacked_sprite(&game->pirateShip); 

  game->gamutoShip.angle = GetTime() * 10; 
  draw_stacked_sprite(&game->gamutoShip); 

  game->ghostShip.angle = GetTime() * 10; 
  draw_stacked_sprite(&game->ghostShip);

  game->jangadaShip.angle = GetTime() * 10; 
  draw_stacked_sprite(&game->jangadaShip);
  
  game->merryShip.angle = GetTime() * 10; 
  draw_stacked_sprite(&game->merryShip);

  game->monsterShip.angle = GetTime() * 10; 
  draw_stacked_sprite(&game->monsterShip);

  game->pinguimShip.angle = GetTime() * 10; 
  draw_stacked_sprite(&game->pinguimShip);

  game->windowsShip.angle = GetTime() * 10; 
  draw_stacked_sprite(&game->windowsShip);

  i32 tintColorLoc2 = GetShaderLocation(game->iceShader, "tintColor");  
  float ice_color2[4] = {0.2f, 0.584f, 0.756f, 1.0f};
  SetShaderValue(game->iceShader, tintColorLoc2, &ice_color2, SHADER_UNIFORM_VEC4); 
  BeginShaderMode(game->iceShader);   
  DrawTextureEx(game->map_overlay, game->map_overlay_offset, 0.0f, 2.0f, WHITE); 
  EndShaderMode();
  
  EndMode2D();
 
  // FPS
  char* fps_str = malloc(sizeof(char) * 32);
  sprintf(fps_str, "FPS: %d", GetFPS());
  DrawText(fps_str, 20, 20, 20, RED);
  
  EndDrawing();  
}

void game_exit(void* ctx){
  Context* game = (Context*) ctx;
  UnloadShader(game->bgShader);
  UnloadTexture(game->map);

  // write_points_to_file("assets/colliders.dat", game->collisions, game->collisions_count); 
}
