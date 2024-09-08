
#ifndef CONTEXT_H
#define CONTEXT_H

#include "../libs/cebus.h"
#include "../libs/raylib/raylib.h"

#include "stacked_sprite.h"

typedef struct Point {
  Vector2 pos;
  f32 radius;
} Point;

void write_points_to_file(const char *filename, Point *points,
                              size_t count) {
  FILE *file = fopen(filename, "wb");
  if (!file) {
    perror("Error opening file for writing");
    return;
  }
  fwrite(&count, sizeof(size_t), 1, file);
  fwrite(points, sizeof(Point), count, file);
  fclose(file);
}

Point *read_points_from_file(const char *filename, i32 *count) {
  FILE *file = fopen(filename, "rb");
  if (!file) {
    perror("Error opening file for reading");
    return NULL;
  }

  fread(count, sizeof(size_t), 1, file);

  Point *points = malloc(sizeof(Point) * (*count + 100));
  if (!points) {
    perror("Error allocating memory");
    fclose(file);
    return NULL;
  }

  fread(points, sizeof(Point), *count, file);
  fclose(file);
  return points;
}

typedef struct Context {
  Shader bgShader;
  Shader iceShader;

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

  i32 collisions_count;
  Point *collisions;

} Context;

#endif
