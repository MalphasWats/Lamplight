#ifndef TILE_ENGINE_H
# define TILE_ENGINE_H

#include "SPIKE.h"

typedef struct Sprite {
    int x;
    int y;
    
    const byte __memx *tile;
} Sprite;

typedef struct Map {
    word cols;
    word rows;
    byte tiles[];
} Map;

typedef struct Image {
    word width;
    word height;
    byte data[];
} Image;

typedef struct Viewport {
    int x;
    int y;
} Viewport;

void draw_tile(const byte __memx *tile, int x, int y);
void draw_map(const Map __memx *map, word x, word y);
void draw_sprite(Sprite *s);

void center_on_sprite(Sprite *s, Map *map);

#endif