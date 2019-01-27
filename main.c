#include <avr/io.h>

#include "main.h"

dword t = 0;

int main (void) 
{    
    initialise();
        
    // display logo
    for(byte y=0 ; y<LOGO_HEIGHT ; y++)
        for(byte x=0 ; x<LOGO_WIDTH ; x++)
            buffer[(y+2)*SCREEN_WIDTH + (x+16)] = LOGO[y*LOGO_WIDTH + x];
    draw();
    
    note(_A4, 90);
    delay_ms(180);
    note(_C5, 60);
    delay_ms(120);
    note(_E5, 60);
    
    delay_ms(SPLASH_DELAY);
    
    byte buttons = 0;
    
    /* Debugging */
    byte delta = 0;
    byte count = 0;
    Sprite d0 = {.x=8*3, .y=0, .tile=6};
    Sprite d1 = {.x=8*2, .y=0, .tile=6};
    Sprite d2 = {.x=8*1, .y=0, .tile=6};
    
    for(ever)
    {
        t = millis();
        
        buttons = ~PINC;
        if ( buttons & _A )
        {
            click();
        }
        
            
        clear_buffer();
        
        draw_map(&level_1, 0, 0);
        
        draw_sprite(&d0);
        draw_sprite(&d1);
        draw_sprite(&d2);
        
        draw();
        
        /* Debugging */
        delta = (millis() - t);
        if (count == 0)
        {
            d0.tile = (delta % 10);
            delta /= 10;
            d1.tile = (delta % 10);
            delta /= 10;
            d2.tile = (delta % 10);
            count = 12;
        }
        count -= 1;
    }
}
