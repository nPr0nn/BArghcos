
#include "collisions.h"
#include "context.h"
#include "points.h"
#include "stacked_sprite.h"

#include <stdio.h>

#define EDITOR 1

#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION 330
#else // PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION 100
#endif

void game_init(void *ctx) {
  Context *game = (Context *)ctx;

  InitAudioDevice();
  game->m = LoadMusicStream("assets/song.mp3");
  PlayMusicStream(game->m);

  game->pirateShip.lap = 0;
  game->pirateShip.progress = 0;

  i32 screenWidth = GetScreenWidth();
  i32 screenHeight = GetScreenHeight();

  // Set the dimensions of the screen
  Vector2 screen_dims = (Vector2){screenWidth, screenHeight};

  // Map
  Image image_map = LoadImage("assets/maps/track2.png");
  // Image image_map_overlay = LoadImage("assets/maps/track22.png");
  game->map_overlay_offset = (Vector2){-10, -9};
  game->map_top_left = (Vector2){0, 0};
  game->map = LoadTextureFromImage(image_map);
  game->map_overlay = game->map;
// game->map_overlay = LoadTextureFromImage(image_map_overlay);

// Ocean Background
#ifndef PLATFORM_WEB
  game->bgShader =
      LoadShader(0, TextFormat("assets/shaders/background.fs", GLSL_VERSION));
#endif
#ifdef PLATFORM_WEB
  game->bgShader = LoadShader(
      0, TextFormat("assets/shaders/background_web.fs", GLSL_VERSION));
#endif

  game->timeLoc = GetShaderLocation(game->bgShader, "time");
  game->playerLoc = GetShaderLocation(game->bgShader, "playerPos");
  i32 resolutionLoc = GetShaderLocation(game->bgShader, "resolution");
  SetShaderValue(game->bgShader, resolutionLoc, &screen_dims,
                 SHADER_UNIFORM_VEC2);

// Ice Outline
#ifndef PLATFORM_WEB
  game->iceShader =
      LoadShader(0, TextFormat("assets/shaders/outline.fs", GLSL_VERSION));
#endif
#ifdef PLATFORM_WEB
  game->iceShader =
      LoadShader(0, TextFormat("assets/shaders/outline_web.fs", GLSL_VERSION));
#endif

#ifndef PLATFORM_WEB
  game->tintShader =
      LoadShader(0, TextFormat("assets/shaders/tint.fs", GLSL_VERSION));
#endif
#ifdef PLATFORM_WEB
  game->tintShader =
      LoadShader(0, TextFormat("assets/shaders/tint_web.fs", GLSL_VERSION));
#endif
  i32 tintColorLoc2 = GetShaderLocation(game->tintShader, "tintColor");
  float tint_color2[4] = {(51) / (255.0f), (149) / (255.0f), (193) / (255.0f),
                          1.0f};
  // float tint_color2[4] = {(211)/(255.0f), (173)/(255.0f),
  // (67)/(255.0f), 1.0f};
  SetShaderValue(game->tintShader, tintColorLoc2, &tint_color2,
                 SHADER_UNIFORM_VEC4);

  game->timeLoc2 = GetShaderLocation(game->iceShader, "time");
  resolutionLoc = GetShaderLocation(game->iceShader, "resolution");
  SetShaderValue(game->iceShader, resolutionLoc, &screen_dims,
                 SHADER_UNIFORM_VEC2);

  // All Ships Settings
  // ----------------------------------------------------------------------
  // pirateShip
  game->pirateShip = (StackedSprite){
      .name = "car",
      .pos = (Vector2){2100, 1486},
      .sprite_sheet_path = "assets/ships/pirateShip.png",
      .num_layers = 15,
      .scale = 1.0,
      .y_offset = 10,
      .angle = 0,
  };
  load_stacked_sprite(&game->pirateShip);

  // gamutoShip
  game->gamutoShip = (StackedSprite){
      .name = "car",
      .pos = (Vector2){2100, 1408},
      .sprite_sheet_path = "assets/ships/gamutoShip.png",
      .num_layers = 15,
      .scale = 1.0,
      .y_offset = 10,
      .angle = 0,
  };
  load_stacked_sprite(&game->gamutoShip);

  // ghostShip
  game->ghostShip = (StackedSprite){
      .name = "car",
      .pos = (Vector2){2150, 1486},
      .sprite_sheet_path = "assets/ships/ghostShip.png",
      .num_layers = 15,
      .scale = 1,
      .y_offset = 10,
      .angle = 0,
  };
  load_stacked_sprite(&game->ghostShip);

  // jangadaShip
  game->jangadaShip = (StackedSprite){
      .name = "car",
      .pos = (Vector2){2150, 1408},
      .sprite_sheet_path = "assets/ships/jangadaShip.png",
      .num_layers = 15,
      .scale = 1,
      .y_offset = 10,
      .angle = 0,
  };
  load_stacked_sprite(&game->jangadaShip);

  // merryShip
  game->merryShip = (StackedSprite){
      .name = "car",
      .pos = (Vector2){2150, 1566},
      .sprite_sheet_path = "assets/ships/merryShip.png",
      .num_layers = 15,
      .scale = 1,
      .y_offset = 10,
      .angle = 0,
  };
  load_stacked_sprite(&game->merryShip);

  // monsterShip
  game->monsterShip = (StackedSprite){
      .name = "car",
      .pos = (Vector2){2100, 1566},
      .sprite_sheet_path = "assets/ships/monsterShip.png",
      .num_layers = 12,
      .scale = 0.75,
      .y_offset = 10,
      .angle = 0,
  };
  load_stacked_sprite(&game->monsterShip);

  // pinguimShip
  game->pinguimShip = (StackedSprite){
      .name = "car",
      .pos = (Vector2){2100, 1642},
      .sprite_sheet_path = "assets/ships/pinguimShip.png",
      .num_layers = 15,
      .scale = 1.0,
      .y_offset = 10,
      .angle = 0,
  };
  load_stacked_sprite(&game->pinguimShip);

  // windowsShip
  game->windowsShip = (StackedSprite){
      .name = "car",
      .pos = (Vector2){2150, 1642},
      .sprite_sheet_path = "assets/ships/windowsShip.png",
      .num_layers = 14,
      .scale = 1.0,
      .y_offset = 10,
      .angle = 0,
  };
  load_stacked_sprite(&game->windowsShip);

  //----------------------------------------------------------------------

  game->camera.target = (Vector2){0, 0};
  game->camera.offset = (Vector2){screenWidth * 0.5f, screenHeight * 0.5f - 64};
  game->camera.rotation = 0.0f;
  game->camera.zoom = 4.5f;

  // Track points

  game->selectedCount = 0;
  game->selected = (Point *)malloc(100 * sizeof(Point));

  game->innerTrack = get_inner_track();
  game->innerTrackCount = 30;

  game->outerTrack = get_outer_track();
  game->outerTrackCount = 31;

  game->checkMarks = get_check_marks();
  game->checkMarkCount = 46;

  create_targets(&game->gamutoShip, game->checkMarks, game->checkMarkCount);
  create_targets(&game->ghostShip, game->checkMarks, game->checkMarkCount);
  create_targets(&game->jangadaShip, game->checkMarks, game->checkMarkCount);
  create_targets(&game->merryShip, game->checkMarks, game->checkMarkCount);
  create_targets(&game->monsterShip, game->checkMarks, game->checkMarkCount);
  create_targets(&game->pinguimShip, game->checkMarks, game->checkMarkCount);
  create_targets(&game->windowsShip, game->checkMarks, game->checkMarkCount);

  // for(i32 i = 0; i < game->checkMarkCount; i++){
  //   printf("track[%d].pos = (Vector2){%f, %f};\n", i,
  //   game->checkMarks[i].pos.x, game->checkMarks[i].pos.y);
  //   printf("track[%d].radius = %f;\n", i, game->checkMarks[i].radius);
  // }

  game->start = true;
  game->end = false;
}

void game_update(Context *game);
void game_draw(Context *game);

void game_loop(void *ctx) {
  Context *game = (Context *)ctx;

  UpdateMusicStream(game->m);

  while(game->end) {
    i32 screenWidth = GetScreenWidth();
    i32 screenHeight = GetScreenHeight();
    
    BeginDrawing();
    ClearBackground((Color){255, 255, 255, 255});
    
    DrawText("Obrigado por jogar! :D", screenWidth/2 - 200, screenHeight/2, 60, BLACK);

    char *position_str = malloc(sizeof(char) * 32);
    sprintf(position_str, "Placar: %d/8", game->position);
    DrawText(position_str, screenWidth/2 - 200, screenHeight/2 - 100, 60, BLACK);

    EndDrawing();

    return;
  }
  
  game_update(game);
  game_draw(game);
}

void update_and_collide(StackedSprite *entt, Context *game) {

  Vector2 old_pos = (Vector2){entt->pos.x, entt->pos.y + entt->y_offset * 0};
  Vector2 new_pos =
      Vector2Add(old_pos, Vector2Scale(entt->vel, GetFrameTime()));

  for (i32 i = 0; i < game->innerTrackCount - 1; i++) {
    Vector2 line_pt1 = game->innerTrack[i].pos;
    Vector2 line_pt2 = game->innerTrack[i + 1].pos;

    Vector2 collision_pt;
    f32 t;
    if (sweptCircleLineCollision(entt->pos, new_pos, entt->radius, line_pt2,
                                 line_pt1, &collision_pt, &t)) {
      resolveCollision(&new_pos, &entt->vel, line_pt2, line_pt1, collision_pt);
      entt->confused = true;
    }
  }

  for (i32 i = 0; i < game->outerTrackCount - 1; i++) {
    Vector2 line_pt1 = game->outerTrack[i].pos;
    Vector2 line_pt2 = game->outerTrack[i + 1].pos;

    Vector2 collision_pt;
    f32 t;
    if (sweptCircleLineCollision(entt->pos, new_pos, entt->radius, line_pt1,
                                 line_pt2, &collision_pt, &t)) {
      resolveCollision(&new_pos, &entt->vel, line_pt1, line_pt2, collision_pt);
      entt->confused = true;
    }
  }

  entt->pos = new_pos;

  if (lineCircle(game->checkMarks[entt->progress].pos,
                 game->checkMarks[entt->progress + 1].pos, entt->pos,
                 entt->radius)) {
    entt->progress += 2;
    entt->real_progress += 1;
    entt->current_target_index += 1;
    if (entt->progress == game->checkMarkCount) {
      entt->progress = 0;
      entt->lap += 1;
      if(entt->lap == 4){
        entt->current_target_index = 0;
      }
      if (game->pirateShip.lap == 4){
        game->end = true;
      }
    }
  }
}

void game_update(Context *game) {
  // printf("player: (%f, %f)\n", game->pirateShip.pos.x,
  // game->pirateShip.pos.y);

  i32 screenWidth = GetScreenWidth();
  i32 screenHeight = GetScreenHeight();

  f32 time = GetTime();
  SetShaderValue(game->bgShader, game->timeLoc, &time, SHADER_UNIFORM_FLOAT);
  SetShaderValue(game->bgShader, game->playerLoc, &game->pirateShip.pos,
                 SHADER_UNIFORM_VEC2);
  SetShaderValue(game->iceShader, game->timeLoc2, &time, SHADER_UNIFORM_FLOAT);

  // Move square and update offset
  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    Vector2 mouse_pos = (Vector2){GetMouseX(), GetMouseY()};
    Vector2 mouse_pos_world = GetScreenToWorld2D(mouse_pos, game->camera);
    game->selected[game->selectedCount].pos =
        (Vector2){mouse_pos_world.x, mouse_pos_world.y};
    game->selected[game->selectedCount].radius = 5;
    game->selectedCount += 1;
  }

  if(game->start == false){   
    update_player(&game->pirateShip);
    update_and_collide(&game->pirateShip, game);

    update_enemy(&game->gamutoShip);
    update_and_collide(&game->gamutoShip, game);

    update_enemy(&game->ghostShip);
    update_and_collide(&game->ghostShip, game);

    update_enemy(&game->jangadaShip);
    update_and_collide(&game->jangadaShip, game);

    update_enemy(&game->merryShip);
    update_and_collide(&game->merryShip, game);

    update_enemy(&game->monsterShip);
    update_and_collide(&game->monsterShip, game);

    update_enemy(&game->pinguimShip);
    update_and_collide(&game->pinguimShip, game);

    update_enemy(&game->windowsShip);
    update_and_collide(&game->windowsShip, game);
  }

  game->camera.target =
      (Vector2){game->pirateShip.pos.x, game->pirateShip.pos.y};
}

void game_draw(Context *game) {
  i32 screenWidth = GetScreenWidth();
  i32 screenHeight = GetScreenHeight();
  
  BeginDrawing();
  ClearBackground((Color){20, 30, 50, 255});

  BeginShaderMode(game->bgShader);
  DrawRectangle(0, 0, screenWidth, screenHeight, BLUE);
  EndShaderMode();

  BeginMode2D(game->camera);

  BeginShaderMode(game->iceShader);
  DrawTextureEx(game->map, (Vector2){0, 0}, 0.0f, 2.0f, WHITE);
  EndShaderMode();

  // game->gamutoShip.angle = GetTime() * 10;
  draw_stacked_sprite(&game->gamutoShip);

  // game->ghostShip.angle = GetTime() * 10;
  draw_stacked_sprite(&game->ghostShip);

  // game->jangadaShip.angle = GetTime() * 10;
  draw_stacked_sprite(&game->jangadaShip);

  // game->merryShip.angle = GetTime() * 10;
  draw_stacked_sprite(&game->merryShip);

  // game->monsterShip.angle = GetTime() * 10;
  draw_stacked_sprite(&game->monsterShip);

  // game->pinguimShip.angle = GetTime() * 10;
  draw_stacked_sprite(&game->pinguimShip);

  // game->windowsShip.angle = GetTime() * 10;
  draw_stacked_sprite(&game->windowsShip);

  draw_stacked_sprite(&game->pirateShip);

  BeginShaderMode(game->tintShader);
  DrawTextureEx(game->map_overlay, game->map_overlay_offset, 0.0f, 2.0f, WHITE);
  EndShaderMode();
  
  // for (i32 i = 0; i < game->innerTrackCount - 1; i++) {
  //   DrawCircleV(game->innerTrack[i].pos, game->innerTrack[i].radius, RED);
  //   DrawLineEx(game->innerTrack[i].pos, game->innerTrack[i + 1].pos, 2, GREEN);
  // }
  // DrawCircleV(game->innerTrack[game->innerTrackCount - 1].pos,
  //             game->innerTrack[game->innerTrackCount - 1].radius, RED);
  //
  // for (i32 i = 0; i < game->outerTrackCount - 1; i++) {
  //   DrawCircleV(game->outerTrack[i].pos, game->outerTrack[i].radius, RED);
  //   DrawLineEx(game->outerTrack[i].pos, game->outerTrack[i + 1].pos, 2, GREEN);
  // }
  // DrawCircleV(game->outerTrack[game->outerTrackCount - 1].pos,
  //             game->outerTrack[game->outerTrackCount - 1].radius, RED);
  //
  // for (i32 i = 0; i < game->checkMarkCount; i++) {
  //   DrawCircleV(game->checkMarks[i].pos, game->checkMarks[i].radius, YELLOW);
  // }
  // if (game->checkMarkCount % 2 == 0) {
  //   for (i32 i = 0; i < game->checkMarkCount; i += 2) {
  //     DrawLineEx(game->checkMarks[i].pos, game->checkMarks[i + 1].pos, 2,
  //                ORANGE);
  //   }
  // }
  //
  // for (i32 i = 0; i < game->gamutoShip.num_targets; i++) {
  //   DrawCircleV(game->gamutoShip.targets[i], 5, GREEN);
  // }

  EndMode2D();

  if (game->start == true){
    DrawText("Press Space to Start", screenWidth / 2 - 200, screenHeight / 2 - 50, 40, BLACK);
    DrawText("Press Space to Start", screenWidth / 2 - 200 + 3, screenHeight / 2 - 50 + 3, 40, WHITE); 
    if( (GetKeyPressed() == KEY_SPACE) || (IsGamepadButtonPressed(0, 5) || IsGamepadButtonPressed(0, 6) || IsGamepadButtonPressed(0, 7) || IsGamepadButtonPressed(0, 8)) ) {
      game->start = false;
    }
  }

  i32 all_progresses[7] = {
      game->gamutoShip.real_progress,  game->ghostShip.real_progress,
      game->jangadaShip.real_progress, game->merryShip.real_progress,
      game->monsterShip.real_progress, game->pinguimShip.real_progress,
      game->windowsShip.real_progress,
  };
  game->position = 8;
  for (i32 i = 0; i < 8; i++) {
    if (all_progresses[i] < game->pirateShip.real_progress) {
      game->position -= 1;
    }
  }

  // FPS
  char* fps_str = malloc(sizeof(char) * 32);
  sprintf(fps_str, "FPS: %d", GetFPS());
  DrawText(fps_str, 20, 20, 40, BLACK);
  DrawText(fps_str, 20+3, 20+3, 40, WHITE);

  char *lap_str = malloc(sizeof(char) * 32);
  sprintf(lap_str, "Lap: %d/3", game->pirateShip.lap);
  DrawText(lap_str, screenWidth - 300, 20, 60, BLACK); 
  DrawText(lap_str, screenWidth - 300 + 3, 20 + 3, 60, WHITE);

  char *position_str = malloc(sizeof(char) * 32);
  sprintf(position_str, "Placar: %d/8", game->position);
  DrawText(position_str, screenWidth - 394, 100, 60, BLACK);
  DrawText(position_str, screenWidth - 394 + 3, 100 + 3, 60, WHITE);

  EndDrawing();
}

void game_exit(void *ctx) {
  Context *game = (Context *)ctx;
  UnloadShader(game->bgShader);
  UnloadTexture(game->map);

  for (i32 i = 0; i < game->selectedCount; i++) {
    printf("track[%d].pos = (Vector2){%f, %f};\n", i, game->selected[i].pos.x,
           game->selected[i].pos.y);
    printf("track[%d].radius = %f;\n", i, game->selected[i].radius);
  }
}
