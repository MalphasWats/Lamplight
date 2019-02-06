#include <avr/io.h>

#include "main.h"
#include "isometric-engine.h"

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
    
    //Sprite d3 = {.x=8*7, .y=0, .tile=&DIGITS[0]};
    //Sprite d4 = {.x=8*6, .y=0, .tile=&DIGITS[0]};
    //Sprite d5 = {.x=8*5, .y=0, .tile=&DIGITS[0]};
    
    int x=0;
    int y=0;
    
    //byte x_ = 0;
    //byte y_ = 0;
    
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
                x += 2;
                y -= 2;
            }
            if ( buttons & _DOWN )
            {
                x -= 2;
                y += 2;
            }
            if ( buttons & _LEFT )
            {
                x -= 2;
                y -= 2;
            }
            if ( buttons & _RIGHT )
            {
                x += 2;
                y += 2;
            }
            
            btn_timer = t+20;
        }
        
        /*if (x < 0)
            x = 0;
        if (y < 0)
            y = 0;*/
        
        set_viewport(x, y);
        clear_buffer();
        
        //draw_map(&level_1, 0, 0, &IMAGES[0]);
        draw_map(&level_1, &IMAGES[0]);
        
        draw_sprite(&d0);
        draw_sprite(&d1);
        draw_sprite(&d2);
        
        //draw_sprite(&d3);
        //draw_sprite(&d4);
        //draw_sprite(&d5);
        
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
            
            /*x_ = x; //abs(x);
            y_ = y; //abs(y);
            
            d0.tile = &DIGITS[(x_ % 10)*8];
            x_ /= 10;
            d1.tile = &DIGITS[(x_ % 10)*8];
            x_ /= 10;
            d2.tile = &DIGITS[(x_ % 10)*8];
            count = 12;
            
            d3.tile = &DIGITS[(y_ % 10)*8];
            y_ /= 10;
            d4.tile = &DIGITS[(y_ % 10)*8];
            y_ /= 10;
            d5.tile = &DIGITS[(y_ % 10)*8];
            count = 12;*/
        }
        count -= 1;
    }
}
