/*
** EPITECH PROJECT, 2023
** set background
** File description:
** set and change texture background
*/
#include "include/my_hunter.h"

static void set_icon(struct sprite *background)
{
    background->cursor.texture = sfTexture_createFromFile("sprites/logo.png",
    NULL);
    background->cursor.sprite = sfSprite_create();
    background->cursor.pos.x = 1400;
    background->cursor.pos.y = 15;
    background->cursor.scale = (sfVector2f){0.3, 0.3};
    sfSprite_setScale(background->cursor.sprite, background->cursor.scale);
    sfSprite_setTexture(background->cursor.sprite, background->cursor.
    texture, sfTrue);
    sfSprite_setPosition(background->cursor.sprite, background->cursor.pos);
    background->proj.texture = sfTexture_createFromFile
    ("sprites/logo_marine.png", NULL);
    background->proj.sprite = sfSprite_create();
    background->proj.pos = (sfVector2f){10, 5};
    background->proj.scale = (sfVector2f){0.25, 0.25};
    sfSprite_setScale(background->proj.sprite, background->proj.scale);
    sfSprite_setTexture(background->proj.sprite, background->proj.texture,
    sfTrue);
    sfSprite_setPosition(background->proj.sprite, background->proj.pos);
}

void set_background(struct sprite *background)
{
    sfFont* font = sfFont_createFromFile("font/arial.ttf");

    background->texture = sfTexture_createFromFile("map.png", NULL);
    background->sprite = sfSprite_create();
    background->pos.x = -140;
    background->pos.y = -25;
    background->compt = 0;
    background->clock = sfClock_create();
    background->score.text = sfText_create();
    sfText_setFont(background->score.text, font);
    sfText_setCharacterSize(background->score.text, 30);
    sfText_setPosition(background->score.text, (sfVector2f){80, 860});
    sfText_setFillColor(background->score.text, sfBlack);
    sfSprite_setTexture(background->sprite, background->texture, sfTrue);
    sfSprite_setPosition(background->sprite, background->pos);
    set_icon(background);
}

static void change_background(struct sprite *background)
{
    background->texture = sfTexture_createFromFile("dressrosa.png", NULL);
    background->sprite = sfSprite_create();
    background->pos.x = 0;
    background->pos.y = 0;
    background->scale = (sfVector2f){1.8, 1.55};
    background->compt = 1;
    sfSprite_setTexture(background->sprite, background->texture, sfTrue);
    sfSprite_setScale(background->sprite, background->scale);
    sfSprite_setPosition(background->sprite, background->pos);
}

static void change_background_final(struct sprite *background)
{
    background->texture = sfTexture_createFromFile("ruche.jpg", NULL);
    background->sprite = sfSprite_create();
    background->pos.x = 0;
    background->pos.y = 0;
    background->scale = (sfVector2f){1.9, 1.7};
    background->compt = 2;
    sfSprite_setTexture(background->sprite, background->texture, sfTrue);
    sfSprite_setScale(background->sprite, background->scale);
    sfSprite_setPosition(background->sprite, background->pos);
}

static void display_time(sfRenderWindow *window, struct sprite *background)
{
    sfTime elapsed = sfClock_getElapsedTime(background->clock);
    float val = sfTime_asSeconds(elapsed);
    char buffer[100];

    background->score.min = (int)(val / 60);
    background->score.sec = (int)(val) % 60;
    buffer[0] = '\0';
    my_strcat(buffer, "Time ");
    my_strcat(buffer, int_to_str(background->score.min));
    my_strcat(buffer, ":");
    my_strcat(buffer, int_to_str(background->score.sec));
    sfText_setString(background->score.text, buffer);
    sfRenderWindow_drawText(window, background->score.text, NULL);
}

void display_background(sfRenderWindow *window, struct sprite *background,
    struct sprite *ennemie)
{
    if (ennemie->kill == 21 && background->compt == 1)
        change_background_final(background);
    if (ennemie->kill == 11 && background->compt == 0)
        change_background(background);
    sfRenderWindow_drawSprite(window, background->sprite, NULL);
    sfRenderWindow_drawSprite(window, background->cursor.sprite, NULL);
    sfRenderWindow_drawSprite(window, background->proj.sprite, NULL);
    display_time(window, background);
}

void set_life_perso(struct sprite *usoop)
{
    usoop->life.bar = sfRectangleShape_create();
    usoop->life.size = (sfVector2f){500, 50};
    sfRectangleShape_setSize(usoop->life.bar, usoop->life.size);
    sfRectangleShape_setFillColor(usoop->life.bar, sfGreen);
    usoop->life.pos = (sfVector2f){875, 30};
    sfRectangleShape_setPosition(usoop->life.bar, usoop->life.pos);
    sfRectangleShape_setOutlineThickness(usoop->life.bar, 5);
    sfRectangleShape_setOutlineColor(usoop->life.bar, sfBlack);
    usoop->back_life.size = (sfVector2f){500, 50};
    usoop->back_life.bar = sfRectangleShape_create();
    sfRectangleShape_setFillColor(usoop->back_life.bar, sfRed);
    sfRectangleShape_setSize(usoop->back_life.bar, usoop->back_life.size);
    sfRectangleShape_setPosition(usoop->back_life.bar, usoop->life.pos);
    sfRectangleShape_setOutlineThickness(usoop->back_life.bar, 5);
    sfRectangleShape_setOutlineColor(usoop->back_life.bar, sfBlack);
}

void set_life_ennemie(struct sprite *ennemie)
{
    ennemie->life.bar = sfRectangleShape_create();
    ennemie->life.size = (sfVector2f){500, 50};
    sfRectangleShape_setSize(ennemie->life.bar, ennemie->life.size);
    sfRectangleShape_setFillColor(ennemie->life.bar, sfGreen);
    ennemie->life.pos = (sfVector2f){150, 30};
    sfRectangleShape_setPosition(ennemie->life.bar, ennemie->life.pos);
    sfRectangleShape_setOutlineThickness(ennemie->life.bar, 5);
    sfRectangleShape_setOutlineColor(ennemie->life.bar, sfBlack);
    ennemie->back_life.size = (sfVector2f){500, 50};
    ennemie->back_life.bar = sfRectangleShape_create();
    sfRectangleShape_setFillColor(ennemie->back_life.bar, sfRed);
    sfRectangleShape_setSize(ennemie->back_life.bar, ennemie->back_life.size);
    sfRectangleShape_setPosition(ennemie->back_life.bar, ennemie->life.pos);
    sfRectangleShape_setOutlineThickness(ennemie->back_life.bar, 5);
    sfRectangleShape_setOutlineColor(ennemie->back_life.bar, sfBlack);
}
