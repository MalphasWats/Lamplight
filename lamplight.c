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
            if ( buttons & _A )
            {
                click();
            }
            
            if ( buttons & _UP )
            {
                player.y -= 1;
                if ( collide_with_world(&player, &VILLAGE) || player.y < 0)
                    player.y += 1;
            }
            if ( buttons & _DOWN )
            {
                player.y += 1;
                if ( collide_with_world(&player, &VILLAGE) || player.y > (VILLAGE.rows-1)*8)
                    player.y -= 1;
            }
            if ( buttons & _LEFT )
            {
                player.x -= 1;
                if ( collide_with_world(&player, &VILLAGE) || player.x < 0)
                    player.x += 1;
            }
            if ( buttons & _RIGHT )
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
        
        draw_map(&VILLAGE, TILESETS[0]);
        
        draw_sprite(&player);
        
        draw();
    }
}
