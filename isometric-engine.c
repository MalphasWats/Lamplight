#include "isometric-engine.h"

Viewport viewport = {.x=0, .y=0};

void draw_tile(const byte __flash *tile, const byte __flash *mask, int x, int y)
{
    /* is the tile actually visible */
    if (x < -7 || x >= SCREEN_WIDTH || y < -7 || y >= SCREEN_HEIGHT)
        return;
    
    
    int y_ = y;
    
    if (y < 0)
        y_ = 0-y;
        
    int tile_start = ((y_ >> 3) * SCREEN_WIDTH) + x;
    
    byte y_offset_a = y & 7; // y % 8
    byte y_offset_b = 8-y_offset_a;
    
    byte tile_index = 0;
    byte tile_width = 8;
    if (x < 0)
    {
        tile_start -= x;
        tile_index = 0-x;
        tile_width -= tile_index;
    }
    
    if (x > SCREEN_WIDTH-8)
    {
        tile_width = SCREEN_WIDTH-x;
    }
    
    if (y < 0)
    {
        y_offset_a = 8;
        y_offset_b = 0-y;
        tile_start -= SCREEN_WIDTH;
    }
    
    if (y > SCREEN_HEIGHT-8)
    {
        y_offset_b = 8;
    }
    
    for(byte tile_offset=0 ; tile_offset<tile_width ; tile_offset++, tile_index++)
    {
        if (y_offset_a < 8)
        {
            buffer[tile_start+tile_offset] &= (mask[tile_index] << y_offset_a) | ~(0xff << y_offset_a);
            buffer[tile_start+tile_offset] |= tile[tile_index] << y_offset_a;
        }
        if (y_offset_b < 8)
        {
            buffer[tile_start+SCREEN_WIDTH+tile_offset] &= (mask[tile_index] >> y_offset_b) | ~(0xff >> y_offset_b);
            buffer[tile_start+SCREEN_WIDTH+tile_offset] |= tile[tile_index] >> y_offset_b;
        }
    }
}

void draw_image(const Image __flash *image, int x, int y)
{
    x -= image->width>>1;
    y -= image->height-8;
    
    if (!visible(image, x, y))
        return;
    
    byte rows = image->height>>3;
    byte cols = image->width>>3;
    
    word mask_offset = rows * image->width;
    
    for(byte r=0 ; r<rows ; r++)
    {
        for(byte c=0 ; c<cols ; c++)
        {
            draw_tile(&image->data[(r*cols+c)*8], &image->data[ ((r*cols+c)*8) + mask_offset ], x+(c*8), y+(r*8));
        }
    }
}

void draw_map(const Map __memx *map, word x, word y, const __flash Image *tileset[])
{
    for(word c=0 ; c<map->cols ; c++)
    {
        for(word r=0 ; r<map->rows ; r++)
        {
            draw_image(tileset[map->tiles[r*map->cols+c]], c*8+(64 - r*8), r*4+(c*4));
        }
    }
}

bool visible(const Image __flash *image, int x, int y)
{
    //TODO: need to include viewport
    
    if (x < SCREEN_WIDTH &&
        x >= 0-image->width &&
        y < SCREEN_HEIGHT &&
        y >= 0-image->height)
        return TRUE;
    
    return FALSE;
}

void draw_sprite(Sprite *s)
{
    draw_tile(s->tile, s->tile, s->x, s->y);
}

void center_on_sprite(Sprite *s, Map *map)
{

}