/*
** EPITECH PROJECT, 2023
** set perso
** File description:
** set all sprites
*/

#include "include/my_hunter.h"

void set_target(struct sprite *usoop)
{
    usoop->cursor.texture = sfTexture_createFromFile("sprites/target.png",
    NULL);
    usoop->cursor.sprite = sfSprite_create();
    usoop->cursor.scale = (sfVector2f){0.05, 0.05};
    sfSprite_setScale(usoop->cursor.sprite, usoop->cursor.scale);
    sfSprite_setTexture(usoop->cursor.sprite, usoop->cursor.texture, sfTrue);
    usoop->proj.texture = sfTexture_createFromFile("sprites/dure.png", NULL);
    usoop->proj.sprite = sfSprite_create();
    usoop->proj.pos = (sfVector2f){10, 850};
    usoop->proj.scale = (sfVector2f){0.15, 0.15};
    sfSprite_setScale(usoop->proj.sprite, usoop->proj.scale);
    sfSprite_setTexture(usoop->proj.sprite, usoop->proj.texture, sfTrue);
    sfSprite_setPosition(usoop->proj.sprite, usoop->proj.pos);
    usoop->bo = 0;
    usoop->win = 0;
    set_life_perso(usoop);
}

void set_perso(sfRenderWindow *window, struct sprite *usoop)
{
    usoop->texture = sfTexture_createFromFile("sprites/usooprun.png",
    NULL);
    usoop->compt = 0;
    usoop->sprite = sfSprite_create();
    usoop->pos.x = 0;
    usoop->pos.y = 650;
    usoop->scale.x = -1.5;
    usoop->scale.y = 1.5;
    usoop->rect.top = 0;
    usoop->rect.left = 0;
    usoop->rect.width = 150;
    usoop->rect.height = 161;
    usoop->perso = 'u';
    usoop->clock = sfClock_create();
    set_target(usoop);
    sfSprite_setScale(usoop->sprite, usoop->scale);
    sfSprite_setTexture(usoop->sprite, usoop->texture, sfTrue);
    sfSprite_setTextureRect(usoop->sprite, usoop->rect);
    sfSprite_setPosition(usoop->sprite, usoop->pos);
}

void set_fire(sfRenderWindow *window, struct sprite *usoop)
{
    usoop->texture = sfTexture_createFromFile("sprites/fireusoop.png",
    NULL);
    usoop->rect.width = 260;
    usoop->rect.height = 220;
    usoop->rect.top = 0;
    usoop->rect.left = 260;
    usoop->scale.x *= -1;
    usoop->pos.y = 560;
    usoop->pos.x = 1100;
    sfSprite_setTexture(usoop->sprite, usoop->texture, sfTrue);
    sfSprite_setTextureRect(usoop->sprite, usoop->rect);
    sfSprite_setScale(usoop->sprite, usoop->scale);
    sfSprite_setPosition(usoop->sprite, usoop->pos);
}

static void set_cursor(struct sprite *ennemie)
{
    ennemie->cursor.texture = sfTexture_createFromFile("sprites/cursor.png",
    NULL);
    ennemie->cursor.sprite = sfSprite_create();
    ennemie->cursor.scale.x = 0.5;
    ennemie->cursor.scale.y = 0.5;
    ennemie->cursor.clock = sfClock_create();
    sfSprite_setScale(ennemie->cursor.sprite, ennemie->cursor.scale);
    sfSprite_setTexture(ennemie->cursor.sprite, ennemie->cursor.texture,
    sfTrue);
    ennemie->music = sfMusic_createFromFile("sound/roblox.wav");
    ennemie->proj.texture = sfTexture_createFromFile("sprites/projectile.png",
    NULL);
    ennemie->proj.sprite = sfSprite_create();
    ennemie->proj.clock = sfClock_create();
    ennemie->touch = 0;
    sfSprite_setTexture(ennemie->proj.sprite, ennemie->proj.texture,
    sfTrue);
    set_life_ennemie(ennemie);
}

void set_ennemie(sfRenderWindow *window, struct sprite *ennemie)
{
    ennemie->texture = sfTexture_createFromFile("sprites/luccirun.png",
    NULL);
    ennemie->compt = 0;
    ennemie->kill = 0;
    ennemie->sprite = sfSprite_create();
    ennemie->pos.x = 1500;
    ennemie->pos.y = 400;
    ennemie->scale.x = 1.2;
    ennemie->scale.y = 1.2;
    ennemie->rect = (sfIntRect){0, 0, 178, 152};
    ennemie->clock = sfClock_create();
    ennemie->speed = 30;
    ennemie->cursor.bo = 0;
    ennemie->proj.act = 0;
    set_cursor(ennemie);
    sfSprite_setScale(ennemie->sprite, ennemie->scale);
    sfSprite_setTexture(ennemie->sprite, ennemie->texture, sfTrue);
    sfSprite_setTextureRect(ennemie->sprite, ennemie->rect);
    sfSprite_setPosition(ennemie->sprite, ennemie->pos);
}
