#ifndef LAMPLIGHT_H
#define LAMPLIGHT_H

#include "GLYPH.h"

#include "tilemap-engine.h"
#include "tiles.h"
#include "maps.h"
#include "ASCII.h"

void lamplight (void);

bool collide_with_world(Sprite* s, const __memx Map* m);
#endif