
#ifndef CONTEXT_H
#define CONTEXT_H

#include "../libs/raylib/raylib.h"
#include "../libs/cebus.h"

#include "stacked_sprite.h"

typedef struct Context{ 
  Camera2D camera; 
  StackedSprite car; 
  StackedSprite chest; 

  // main2.c
  int *array;
  Vector2 squarePos;
  Vector2 offset;   
  i32 square_size;
  i32 checker_size; 
} Context;

#endif
