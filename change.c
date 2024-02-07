/*
** EPITECH PROJECT, 2023
** change
** File description:
** change perso
*/
#include "include/my_hunter.h"

static void change_proj(struct sprite *ennemie)
{
    ennemie->proj.texture = sfTexture_createFromFile("sprites/bras.png",
    NULL);
    ennemie->proj.act = 0;
    sfClock_restart(ennemie->proj.clock);
    sfSprite_setTexture(ennemie->proj.sprite, ennemie->proj.texture,
    sfTrue);
    sfSprite_setPosition(ennemie->proj.sprite, ennemie->proj.pos);
    ennemie->life.size.x = 500;
    sfRectangleShape_setSize(ennemie->life.bar, ennemie->life.size);
}

void change_ennemie(struct sprite *ennemie)
{
    ennemie->texture = sfTexture_createFromFile("sprites/doflamingo.png",
    NULL);
    ennemie->compt = 0;
    ennemie->rect.width = 225;
    ennemie->rect.height = 186;
    ennemie->rect.top = 0;
    ennemie->rect.left = 0;
    ennemie->kill += 1;
    ennemie->speed = ennemie->speed > 0 ? ennemie->speed + 50 :
    ennemie->speed - 50;
    sfSprite_setTexture(ennemie->sprite, ennemie->texture, sfTrue);
    sfSprite_setTextureRect(ennemie->sprite, ennemie->rect);
    change_proj(ennemie);
}

void change_skin(struct sprite *usoop, struct sprite *ennemie)
{
    usoop->texture = sfTexture_createFromFile("sprites/luffyfire.png",
    NULL);
    usoop->compt = 6;
    usoop->rect.width = 258;
    usoop->rect.height = 131;
    usoop->rect.top = 0;
    usoop->rect.left = 6 * 258;
    usoop->pos.y = 650;
    usoop->pos.x = 1100;
    usoop->perso = 'l';
    change_ennemie(ennemie);
    usoop->bo = 1;
    sfSprite_setTexture(usoop->sprite, usoop->texture, sfTrue);
    sfSprite_setTextureRect(usoop->sprite, usoop->rect);
    sfSprite_setPosition(usoop->sprite, usoop->pos);
}

void set_pos_cursor(struct sprite *usoop, sfRenderWindow *window)
{
    sfVector2i mousePosition = (sfVector2i)sfMouse_getPositionRenderWindow
    (window);

    sfSprite_setPosition(usoop->cursor.sprite, (sfVector2f){(float)
    mousePosition.x - 10, (float)mousePosition.y - 10});
}

static void barbe_noir(struct sprite *ennemie)
{
    ennemie->texture = sfTexture_createFromFile("sprites/barbenoir.png",
    NULL);
    ennemie->compt = 0;
    ennemie->rect.width = 251;
    ennemie->rect.height = 190;
    ennemie->rect.top = 0;
    ennemie->rect.left = 0;
    ennemie->pos.y = 500;
    ennemie->pos.x = 50;
    ennemie->scale.x = 1.2;
    sfSprite_setScale(ennemie->sprite, ennemie->scale);
    sfSprite_setTexture(ennemie->sprite, ennemie->texture, sfTrue);
    sfSprite_setTextureRect(ennemie->sprite, ennemie->rect);
    sfSprite_setPosition(ennemie->sprite, ennemie->pos);
    ennemie->life.size.x = 500;
    sfRectangleShape_setSize(ennemie->life.bar, ennemie->life.size);
}

void gearth_fourth(struct sprite *usoop, struct sprite *ennemie)
{
    usoop->texture = sfTexture_createFromFile("sprites/gearfourth.png",
    NULL);
    usoop->compt = 0;
    usoop->rect.width = 304;
    usoop->rect.height = 216;
    usoop->rect.top = 0;
    usoop->rect.left = 0;
    usoop->pos.y = 400;
    usoop->pos.x = 750 * 2;
    usoop->perso = 'g';
    usoop->scale.x = -1.5;
    barbe_noir(ennemie);
    sfSprite_setScale(usoop->sprite, usoop->scale);
    sfSprite_setPosition(usoop->sprite, usoop->pos);
    sfSprite_setTexture(usoop->sprite, usoop->texture, sfTrue);
    sfSprite_setTextureRect(usoop->sprite, usoop->rect);
}
