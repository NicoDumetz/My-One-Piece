/*
** EPITECH PROJECT, 2023
** action
** File description:
** all action of my_hunter
*/

#include "include/my_hunter.h"

static float myabs(float a)
{
    return a < 0 ? -a : a;
}

static float lerp(float a, float b, float time)
{
    return a + time * (b - a);
}

static void if_touch(struct sprite *ennemie)
{
    ennemie->touch = 1;
    ennemie->cursor.bo = 1;
    sfClock_restart(ennemie->cursor.clock);
    sfSprite_setPosition(ennemie->cursor.sprite, ennemie->cursor.pos);
    sfClock_restart(ennemie->proj.clock);
    sfSprite_setPosition(ennemie->proj.sprite, ennemie->proj.pos);
    sfMusic_play(ennemie->music);
    sfMusic_setPlayingOffset(ennemie->music, sfSeconds(0));
    ennemie->life.size.x -= 50;
    sfRectangleShape_setSize(ennemie->life.bar, ennemie->life.size);
}

void respawn_ennemie(struct sprite *ennemie)
{
    ennemie->pos.y = my_random(200, 650);
    ennemie->pos.x = my_random(0, 99) < 50 ? -50 : 1600;
    ennemie->speed = ennemie->pos.x > 0 ? ennemie->speed : -ennemie->speed;
    ennemie->scale.x = ennemie->pos.x > 0 ? 1.5 : -1.5;
    sfSprite_setScale(ennemie->sprite, ennemie->scale);
    sfSprite_setPosition(ennemie->sprite, ennemie->pos);
}

void check_death(struct sprite *ennemie, sfEvent event, sfRenderWindow
    *window, struct sprite *usoop)
{
    int mouseX = event.mouseButton.x;
    int mouseY = event.mouseButton.y;
    sfFloatRect spriteBounds = sfSprite_getGlobalBounds(ennemie->sprite);

    ennemie->cursor.pos.x = mouseX - (118 / 2);
    ennemie->cursor.pos.y = mouseY - (117 / 2);
    if (sfFloatRect_contains(&spriteBounds, mouseX, mouseY)) {
        if_touch(ennemie);
    } else {
        usoop->life.size.x -= 100;
        sfRectangleShape_setSize(usoop->life.bar, usoop->life.size);
    }
}

static void proj_touch(struct sprite *ennemie)
{
    sfFloatRect spriteBounds = sfSprite_getGlobalBounds(ennemie->sprite);

    if ( myabs(ennemie->proj.pos.x - ennemie->proj.mousepos.x) < 0.001f &&
    myabs(ennemie->proj.pos.y - ennemie->proj.mousepos.y) < 0.001f) {
        ennemie->proj.act = 0;
        sfSprite_setPosition(ennemie->proj.sprite, ennemie->proj.pos);
        if (ennemie->touch == 1) {
            ennemie->touch = 0;
            respawn_ennemie(ennemie);
            ennemie->kill += 1;
        }
    }
}

void calculate_coord_proj(sfRenderWindow *window, struct sprite *usoop,
    struct sprite *ennemie)
{
    sfTime deltatime = sfClock_getElapsedTime(ennemie->clock);
    float second = sfTime_asSeconds(deltatime);

    if (ennemie->proj.act == 1) {
        sfRenderWindow_drawSprite(window, ennemie->proj.sprite, NULL);
        ennemie->proj.pos.x = lerp(ennemie->proj.pos.x, ennemie->proj.
        mousepos.x, second * 9.0f);
        ennemie->proj.pos.y = lerp(ennemie->proj.pos.y, ennemie->proj.
        mousepos.y, second * 9.0f);
        sfSprite_setPosition(ennemie->proj.sprite, ennemie->proj.pos);
        proj_touch(ennemie);
    }
}
