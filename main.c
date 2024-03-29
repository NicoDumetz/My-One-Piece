/*
** EPITECH PROJECT, 2023
** my_hunter main
** File description:
** main of my hunter game
*/
#include "include/my_hunter.h"

static void lunch_fire(sfRenderWindow *window, sfEvent event,
    struct sprite *usoop, struct sprite *ennemie)
{
    sfVector2u windowSize = sfRenderWindow_getSize(window);
    float scale_X = (float)windowSize.x / 1500;
    float scale_Y = (float)windowSize.y / 900;

    usoop->bo = 2;
    ennemie->proj.act = 1;
    ennemie->proj.pos = (sfVector2f){1250, 680};
    ennemie->proj.mousepos = (sfVector2i)
    sfMouse_getPositionRenderWindow(window);
    ennemie->proj.mousepos.x = ennemie->proj.mousepos.x / scale_X;
    ennemie->proj.mousepos.y = ennemie->proj.mousepos.y / scale_Y;
    ennemie->proj.angle = atan2(ennemie->proj.mousepos.y -
    ennemie->proj.pos.y, ennemie->proj.mousepos.x -
    ennemie->proj.pos.x) * 180 / PI;
    ennemie->proj.angle += 180;
    sfSprite_setRotation(ennemie->proj.sprite, ennemie->proj.angle);
    check_death(ennemie, event, window, usoop);
}

void key_pressed(sfRenderWindow *window, sfEvent event,
    struct sprite *usoop, struct sprite *ennemie)
{
    if (event.mouseButton.button == sfMouseLeft)
        if (usoop->bo == 1) {
            lunch_fire(window, event, usoop, ennemie);
        }
        if (usoop->bo == 5)
            check_death_gear(ennemie, event, window, usoop);
}

void pop_event(sfRenderWindow *window, struct sprite *usoop, struct sprite
    *ennemie, struct sprite *background)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
        if ( event.type == sfEvtKeyPressed ||
            event.type == sfEvtMouseButtonPressed)
            key_pressed(window, event, usoop, ennemie);
        if (usoop->life.size.x <= 0) {
            usoop->win = 1;
            usoop->life.size.x = 100;
        }
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyEscape)
            background->pause = 1;
        if ((event.type == sfEvtKeyPressed || event.key.code ==
        sfKeyEscape) && usoop->win > 0)
            sfRenderWindow_close(window);
    }
}

static void display_life_bar(sfRenderWindow *window, struct sprite *usoop,
    struct sprite *ennemie)
{
    if (usoop->bo < 6) {
        sfRenderWindow_drawRectangleShape(window, usoop->back_life.bar, NULL);
        sfRenderWindow_drawRectangleShape(window, usoop->life.bar, NULL);
        sfRenderWindow_drawRectangleShape(window, ennemie->back_life.bar,
        NULL);
        sfRenderWindow_drawRectangleShape(window, ennemie->life.bar, NULL);
    }
}

static void disp_cursor(sfRenderWindow *window, struct sprite *ennemie)
{
    sfTime elapsed = sfClock_getElapsedTime(ennemie->cursor.clock);

    if (ennemie->cursor.bo == 1) {
        sfRenderWindow_drawSprite(window, ennemie->cursor.sprite, NULL);
        if (sfTime_asSeconds(elapsed) >= 0.1)
            ennemie->cursor.bo = 0;
    }
}

static void display(sfRenderWindow *window, struct sprite *usoop,
    struct sprite *ennemie, struct sprite *background)
{
    if (usoop->win > 0)
        return end_game(window, background, usoop);
    if (background->pause == 1)
        return pause_game(window, background, usoop);
    display_background(window, background, ennemie);
    sfRenderWindow_drawSprite(window, ennemie->sprite, NULL);
    sfRenderWindow_drawSprite(window, usoop->sprite, NULL);
    disp_cursor(window, ennemie);
    if (usoop->bo == 2)
        sfRenderWindow_drawSprite(window, usoop->proj.sprite, NULL);
    calculate_coord_proj(window, usoop, ennemie);
    set_pos_cursor(usoop, window);
    sfRenderWindow_drawSprite(window, usoop->cursor.sprite, NULL);
    display_life_bar(window, usoop, ennemie);
    sfRenderWindow_display(window);
}

static void set_music(struct sprite *background)
{
    background->music = sfMusic_createFromFile("sound/weare.ogg");
    sfMusic_setLoop(background->music, sfTrue);
    sfMusic_setVolume(background->music, 10);
    sfMusic_play(background->music);
}

void game(sfRenderWindow *window, struct sprite *usoop,
    struct sprite *ennemie, struct sprite *background)
{
    while (sfRenderWindow_isOpen(window)) {
        pop_event(window, usoop, ennemie, background);
        sfRenderWindow_clear(window, sfBlack);
        animation(window, usoop, ennemie);
        display(window, usoop, ennemie, background);
    }
}

int my_hunter(void)
{
    sfVideoMode mode = {1500, 900, 32};
    sfRenderWindow *window = sfRenderWindow_create(mode, "My One Piece",
    sfResize | sfClose, NULL);
    struct sprite usoop;
    struct sprite ennemie;
    struct sprite background;

    sfRenderWindow_setFramerateLimit(window, 60);
    set_music(&background);
    set_perso(window, &usoop);
    set_ennemie(window, &ennemie);
    set_background(&background);
    sfRenderWindow_setMouseCursorVisible(window, sfFalse);
    game(window, &usoop, &ennemie, &background);
    cleanup(&usoop, &ennemie, &background);
    sfRenderWindow_destroy(window);
    return 0;
}
