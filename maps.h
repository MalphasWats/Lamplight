#ifndef MAPS_H
#define MAPS_H

#include "GLYPH.h"
#include "tilemap-engine.h"
#include "tiles.h"

#define MAX_PORTALS 5

typedef struct Zone {
    uint8_t x_in;
    uint8_t y_in;
    uint8_t x_out;
    uint8_t y_out;

    const __flash Map* map;

    uint8_t num_portals;
    struct Zone* portals[MAX_PORTALS];
    struct Zone* return_to;
} Zone;

static const __flash Map VILLAGE_MAP = {
    .cols = 20,
    .rows = 12,
    .tileset = &VILLAGE_TILES[0],       //Village set
    .tiles = {

	 11,  11,  11,  11,  11,  11,  15,  15,  15,  11,
	 11,   5,   6,   0,   0,   0,   2,   0,  39,  41,

	 17,  15,  15,  15,  15,  15,   5,   2,   0,  15,
	 15,  11,  11,   0,   4,   0,   0,   0,  43,  46,

	 17,   0,  31,  33,   0,   0,   0,   0,   4,   0,
	  0,  15,  17,   0,   0,   0,   2,   0,   0,  36,

	 17,   7,  35,  38,   0,   2,  31,  33,  19,  20,
	 21,   0,  17,   0,  11,   0,  11,   0,   4,   0,

	 17,   0,   0,  10,   0,   0,  35,  38,   0,   0,
	  0,   0,  17,  11,  13,  16,  13,  11,  11,  11,

	 17,   9,   2,  31,  33,  10,   0,  16,   0,   6,
	  0,   2,  15,  15,  15,  10,  15,  15,  15,  17,

	 17,   0,   0,  35,  38,   0,   0,   0,   0,  24,
	 36,   0,   0,  14,   0,   0,   0,   0,  22,  17,

	 17,   6,   3,   0,  10,   0,   2,   0,  14,   0,
	  0,  12,   0,   0,   8,   8,   8,   8,   8,  17,

	 17,  11,  11,  11,  11,   0,   0,   0,   0,   0,
	  0,   0,   0,   0,   8,   8,  26,   8,   8,  17,

	 15,  15,  15,  15,  17,   3,   4,  11,   0,   0,
	 36,  11,   3,   6,   8,   8,   8,   8,   8,  17,

	  6,  27,  29,   2,  17,  11,  11,  13,  36,  16,
	  0,  13,  11,  11,  11,  11,  11,  11,  11,  17,

	  0,   2,   0,   4,  15,  15,  15,  15,   0,  10,
	  0,  15,  15,  15,  15,  15,  15,  15,  15,  15,
    }
};

static const __flash Map HOUSE_MAP = {
    .cols = 16,
    .rows = 8,
    .tileset = &VILLAGE_TILES[0],
    .tiles = {
        0, 0, 0, 0,   47,  53,  53,  53,  53,  53,  53,  53,   0, 0, 0, 0,
        0, 0, 0, 0,   49,  30,   0,  37,   0,  34,   0,  49,   0, 0, 0, 0,
        0, 0, 0, 0,   49,   0,   0,   0,   0,   0,   0,  49,   0, 0, 0, 0,
        0, 0, 0, 0,   49,   0,   0,   0,  54,   0,   0,  49,   0, 0, 0, 0,
        0, 0, 0, 0,   49,  45,   0,   0,  55,  56,   0,  49,   0, 0, 0, 0,
        0, 0, 0, 0,   49,  61,   0,   0,   0,   0,   0,  49,   0, 0, 0, 0,
        0, 0, 0, 0,   49,   0,   0,   0,   0,   0,   0,  49,   0, 0, 0, 0,
        0, 0, 0, 0,   51,  53,  53,  53,   0,  53,  53,  51,   0, 0, 0, 0,
    },
};

Zone VILLAGE;
Zone HOUSE;

static void inline build_zones(void)
{
    VILLAGE = (Zone){
        .x_in = 9*8,
        .y_in = 10*8,
        .x_out = 9*8,
        .y_out = 10*8,
        .map = &VILLAGE_MAP,

        .return_to = &VILLAGE,

        .num_portals = 1,
        .portals = {
            &HOUSE,
        }
    };

    HOUSE = (Zone){
        .x_in = 7*8,
        .y_in = 4*8,
        .x_out = 8*8,
        .y_out = 7*8,
        .map = &HOUSE_MAP,

        .return_to = &VILLAGE,

        .num_portals = 0,
    };
}

#endif
