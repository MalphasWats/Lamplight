#include "lamplight.h"

void lamplight (void) 
{    
    uint8_t buttons = 0;
    
    Sprite player = {.x=9*8, .y=10*8, .tile=&MOBS[PLAYER], .mask=&MOB_MASKS[PLAYER]};
    
    uint32_t t = 0;
    uint32_t btn_timer=0;
    
    for(ever)
    {
        t = millis();
        
        buttons = read_buttons();
        if (btn_timer <= t)
        {
            if ( buttons & BTN_A )
            {
                click();
            }
            
            if ( buttons & BTN_UP )
            {
                player.y -= 1;
                if ( collide_with_world(&player, &VILLAGE) || player.y < 0)
                    player.y += 1;
            }
            if ( buttons & BTN_DOWN )
            {
                player.y += 1;
                if ( collide_with_world(&player, &VILLAGE) || player.y > (VILLAGE.rows-1)*8)
                    player.y -= 1;
            }
            if ( buttons & BTN_LEFT )
            {
                player.x -= 1;
                if ( collide_with_world(&player, &VILLAGE) || player.x < 0)
                    player.x += 1;
            }
            if ( buttons & BTN_RIGHT )
            {
                player.x += 1;
                if ( collide_with_world(&player, &VILLAGE) || player.x > (VILLAGE.cols-1)*8)
                    player.x -= 1;
            }
            
            //TODO: lazy
            btn_timer = t+20;
        }
        
        clear_buffer();
        
        center_on_sprite(&player, &VILLAGE);
        
        draw_map(&VILLAGE);
        
        draw_sprite(&player);
        
        draw();
    }
}

bool collide_with_world(Sprite* s, const __memx Map* m)
{
    return tile_at_xy(m, s->x, s->y) & 1;
}
