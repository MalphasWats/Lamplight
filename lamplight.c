#include "lamplight.h"

void lamplight (void)
{
    uint8_t buttons = 0;

    build_zones();

    Zone* current_zone = &VILLAGE;
    const __flash Map* current_map = current_zone->map;

    Sprite player = {
        .x=current_zone->x_out+4,
        .y=current_zone->y_out+4,
        .width=8,
        .height=8,
        .tile=PLAYER_TILE,
        .mask=PLAYER_MASK
    };

    uint32_t t = 0;
    uint32_t move_timer=0;
    uint32_t action_timer=0;

    for(ever)
    {
        t = millis();

        buttons = read_buttons();
        if (move_timer <= t)
        {
            if ( buttons & BTN_UP )
            {
                player.y -= 1;
                if ( collide_with_world(&player, current_map) || player.y < 0)
                    player.y += 1;
            }
            if ( buttons & BTN_DOWN )
            {
                player.y += 1;
                if ( collide_with_world(&player, current_map) || player.y > (current_map->rows)*8)
                    player.y -= 1;
            }
            if ( buttons & BTN_LEFT )
            {
                player.x -= 1;
                if ( collide_with_world(&player, current_map) || player.x < 0)
                    player.x += 1;
            }
            if ( buttons & BTN_RIGHT )
            {
                player.x += 1;
                if ( collide_with_world(&player, current_map) || player.x > (current_map->cols)*8)
                    player.x -= 1;
            }
            move_timer = t+20;
        }

        if (action_timer <= t)
        {
            if ( buttons & BTN_A )
            {
                click();
                current_zone = scan_portals(&player, current_zone);
                current_map = current_zone->map;
                action_timer = t+200;
            }

        }

        clear_buffer();

        center_on_sprite(&player, current_map);

        draw_map(current_map);

        draw_sprite(&player);

        draw();
    }
}

bool collide_with_world(Sprite* s, const __memx Map* m)
{
    return tile_at_xy(m, s->x, s->y) & 1;
}

Zone* scan_portals(Sprite* player, Zone* current_zone)
{
    if (player->x > current_zone->x_out &&
        player->x < current_zone->x_out+8 &&
        player->y > current_zone->y_out &&
        player->y < current_zone->y_out+8)
    {
        player->x = current_zone->x_in+4;
        player->y = current_zone->y_in+4;
        return current_zone->return_to;
    }

    for(uint8_t i=0 ; i<current_zone->num_portals ; i++)
    {
        if (player->x > current_zone->portals[i]->x_in &&
            player->x < current_zone->portals[i]->x_in+8 &&
            player->y > current_zone->portals[i]->y_in &&
            player->y < current_zone->portals[i]->y_in+8)
        {
            player->x = current_zone->portals[i]->x_out+4;
            player->y = current_zone->portals[i]->y_out+4;
            return current_zone->portals[i];
        }
    }
    return current_zone;
}
