/*
** EPITECH PROJECT, 2023
** animation of sprite
** File description:
** all animation
*/

#include "include/my_hunter.h"

void animation_fire(sfRenderWindow *window, struct sprite *usoop)
{
    sfTime elapsed = sfClock_getElapsedTime(usoop->clock);

    if (sfTime_asSeconds(elapsed) >= 0.15) {
        sfClock_restart(usoop->clock);
        if (usoop->compt == 5) {
            usoop->compt = 0;
            usoop->rect.left = 0;
        } else
            usoop->rect.left += usoop->rect.width;
        sfSprite_setTextureRect(usoop->sprite, usoop->rect);
        if (usoop->rect.left == 260)
            usoop->bo = 1;
        usoop->compt++;
    }
}

void animation_fire_luffy(sfRenderWindow *window, struct sprite *usoop)
{
    sfTime elapsed = sfClock_getElapsedTime(usoop->clock);

    if (sfTime_asSeconds(elapsed) >= 0.2) {
        sfClock_restart(usoop->clock);
        if (usoop->compt == 10) {
            usoop->compt = 0;
            usoop->rect.left = 0;
        } else
            usoop->rect.left += usoop->rect.width;
        sfSprite_setTextureRect(usoop->sprite, usoop->rect);
        if (usoop->rect.left == 6 * 258)
            usoop->bo = 1;
        usoop->compt++;
    }
}

void animation_walk(sfRenderWindow *window, struct sprite *usoop)
{
    sfTime elapsed = sfClock_getElapsedTime(usoop->clock);

    if (usoop->pos.x >= 1450) {
        usoop->bo = 1;
        return set_fire(window, usoop);
    }
    if (sfTime_asSeconds(elapsed) >= 0.1) {
        usoop->pos.x += 30;
        sfSprite_setPosition(usoop->sprite, usoop->pos);
        sfClock_restart(usoop->clock);
        if (usoop->compt == 5) {
            usoop->compt = 0;
            usoop->rect.left = 0;
        } else
            usoop->rect.left += usoop->rect.width;
        sfSprite_setTextureRect(usoop->sprite, usoop->rect);
        usoop->compt++;
    }
}

void animation_ennemie(sfRenderWindow *window, struct sprite *ennemie, struct
    sprite *usoop)
{
    sfTime elapsed = sfClock_getElapsedTime(ennemie->clock);

    if (usoop->bo == 0)
        return;
    sfSprite_setPosition(ennemie->sprite, ennemie->pos);
    if (sfTime_asSeconds(elapsed) >= 0.1) {
        if ((ennemie->pos.x <= -50 && ennemie->speed > 0) || (ennemie->pos.x
        >= 1600 && ennemie->speed < 0)) {
            respawn_ennemie(ennemie);
        } else
            ennemie->pos.x -= ennemie->speed;
        sfClock_restart(ennemie->clock);
        if (ennemie->compt == 5) {
            ennemie->compt = 0;
            ennemie->rect.left = 0;
        } else
            ennemie->rect.left += ennemie->rect.width;
        sfSprite_setTextureRect(ennemie->sprite, ennemie->rect);
        ennemie->compt++;
    }
}

static void set_scene(struct sprite *usoop, struct sprite *ennemie)
{
    if (usoop->scale.x > -4 && usoop->scale.y < 3) {
        usoop->scale.x += usoop->scale.x > 0 ? 0.01 : -0.01;
        usoop->scale.y += usoop->scale.y > 0 ? 0.01 : -0.01;
        sfSprite_setScale(usoop->sprite, usoop->scale);
        usoop->pos.y -= 2;
        sfSprite_setPosition(usoop->sprite, usoop->pos);
        ennemie->scale.x += ennemie->scale.x > 0 ? 0.01 : -0.01;
        ennemie->scale.y += ennemie->scale.y > 0 ? 0.01 : -0.01;
        sfSprite_setScale(ennemie->sprite, ennemie->scale);
        ennemie->pos.y -= 2;
        sfSprite_setPosition(ennemie->sprite, ennemie->pos);
    }
}

static void animation_gear(struct sprite *usoop)
{
    sfTime elapsed = sfClock_getElapsedTime(usoop->clock);

    if (sfTime_asSeconds(elapsed) >= 0.2) {
        sfClock_restart(usoop->clock);
        if (usoop->compt == 6) {
            usoop->compt = 3;
            usoop->rect.left = 3 * usoop->rect.width;
        } else
            usoop->rect.left += usoop->rect.width;
        sfSprite_setTextureRect(usoop->sprite, usoop->rect);
        usoop->compt++;
    }
}

static void animation_barbe(struct sprite *ennemie)
{
    sfTime elapsed = sfClock_getElapsedTime(ennemie->clock);

    if (sfTime_asSeconds(elapsed) >= 0.5) {
        sfClock_restart(ennemie->clock);
        if (ennemie->compt == 4) {
            ennemie->compt = 0;
            ennemie->rect.left = 0;
        } else
            ennemie->rect.left += ennemie->rect.width;
        sfSprite_setTextureRect(ennemie->sprite, ennemie->rect);
        ennemie->compt++;
    }
}

static void animation_final(struct sprite *usoop, struct sprite *ennemie)
{
    if (usoop->bo == 9)
        return die_end(usoop, ennemie);
    animation_barbe(ennemie);
    if (usoop->bo == 8)
        return big_fist(usoop);
    if (usoop->bo == 6)
        return fly_luffy(usoop);
    if (usoop->bo == 5) {
        set_scene(usoop, ennemie);
        usoop->life.size.x -= usoop->life.size.x <= 0 ? 0 : 0.3;
        sfRectangleShape_setSize(usoop->life.bar, usoop->life.size);
    }
    if (ennemie->life.size.x <= 0)
        usoop->bo = 6;
    animation_gear(usoop);
}

void animation(sfRenderWindow *window, struct sprite *usoop,
    struct sprite *ennemie)
{
    if (usoop->bo >= 5)
        return animation_final(usoop, ennemie);
    if (ennemie->kill == 21) {
        usoop->bo = 5;
        return gearth_fourth(usoop, ennemie);
    }
    if (ennemie->kill == 10)
        change_skin(usoop, ennemie);
    animation_ennemie(window, ennemie, usoop);
    if (usoop->bo == 2 && usoop->perso == 'l')
        return animation_fire_luffy(window, usoop);
    if (usoop->bo == 2 && usoop->perso == 'u')
        return animation_fire(window, usoop);
    if (usoop->bo == 1) {
        usoop->compt = usoop->perso == 'u' ? 1 : 6;
        return;
    }
    if (usoop->bo == 0)
        animation_walk(window, usoop);
}
