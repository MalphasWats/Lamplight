#include <avr/io.h>

#include "main.h"

dword t = 0;

int main (void) 
{    
    initialise();
    
    byte buttons = 0;
    
    /* Debugging */
    byte delta = 0;
    byte count = 0;
    Sprite d0 = {.x=8*3, .y=0, .tile=&DIGITS[0]};
    Sprite d1 = {.x=8*2, .y=0, .tile=&DIGITS[0]};
    Sprite d2 = {.x=8*1, .y=0, .tile=&DIGITS[0]};
    
    //int x=0;
    //int y=0;
    
    Sprite player = {.x=9*8, .y=10*8, .tile=&MOBS[PLAYER], .mask=&MOB_MASKS[PLAYER]};
    
    dword btn_timer=0;
    
    for(ever)
    {
        t = millis();
        
        buttons = ~PINC;
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
        
        //set_viewport(player.x-64, player.y-32);
        center_on_sprite(&player, &VILLAGE);
        
        draw_map(&VILLAGE, TILESETS[0]);
        
        draw_sprite(&player);
        
        draw_sprite(&d0);
        draw_sprite(&d1);
        draw_sprite(&d2);
        
        draw();
        
        /* Debugging */
        delta = (millis() - t);
        if (count == 0)
        {
            d0.tile = &DIGITS[(delta % 10)*8];
            delta /= 10;
            d1.tile = &DIGITS[(delta % 10)*8];
            delta /= 10;
            d2.tile = &DIGITS[(delta % 10)*8];
            count = 12;
        }
        count -= 1;
    }
}
