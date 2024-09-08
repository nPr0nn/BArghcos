
#ifndef CONTEXT_H
#define CONTEXT_H

#include "../libs/cebus.h"
#include "../libs/raylib/raylib.h"

#include "stacked_sprite.h"
#include "points.h"

typedef struct Context {
  bool start;

  Music m;
  i32 position;

  Shader bgShader;
  Shader iceShader;
  Shader tintShader;

  bool end;

  i32 timeLoc;
  i32 timeLoc2;

  i32 playerLoc;

  Camera2D camera;

  StackedSprite gamutoShip;
  StackedSprite ghostShip;
  StackedSprite jangadaShip;
  StackedSprite merryShip;
  StackedSprite monsterShip;
  StackedSprite pinguimShip;
  StackedSprite pirateShip;
  StackedSprite windowsShip;

  Texture2D map;
  Texture2D map_overlay;
  Vector2 map_overlay_offset;
  Vector2 map_top_left;

  i32 selectedCount;
  Point *selected;
  
  i32 checkMarkCount;
  Point *checkMarks;
  
  i32 innerTrackCount;
  Point *innerTrack;

  i32 outerTrackCount;
  Point *outerTrack;

} Context;

#endif
