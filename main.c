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
    
    for(ever)
    {
        t = millis();
        
        buttons = ~PINC;
        if ( buttons & _A )
        {
            click();
        }
        
        clear_buffer();
        draw_map(&level_1, 0, 0, &IMAGES[0]);
        
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
