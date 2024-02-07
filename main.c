/*
** EPITECH PROJECT, 2023
** my_hunter main
** File description:
** main of my hunter game
*/
#include "include/my_hunter.h"

void key_pressed(sfRenderWindow *window, sfEvent event,
    struct sprite *usoop, struct sprite *ennemie)
{
    if (event.mouseButton.button == sfMouseLeft)
        if (usoop->bo == 1) {
            usoop->bo = 2;
            ennemie->proj.act = 1;
            ennemie->proj.pos = (sfVector2f){1250, 680};
            ennemie->proj.mousepos = (sfVector2i)
            sfMouse_getPositionRenderWindow(window);
            ennemie->proj.angle = atan2(ennemie->proj.mousepos.y -
            ennemie->proj.pos.y, ennemie->proj.mousepos.x - ennemie->proj.pos.
            x) * 180 / PI;
            ennemie->proj.angle += 180;
            sfSprite_setRotation(ennemie->proj.sprite, ennemie->proj.angle);
            check_death(ennemie, event, window, usoop);
        }
        if (usoop->bo == 5)
            check_death_gear(ennemie, event, window, usoop);
}

void pop_event(sfRenderWindow *window, struct sprite *usoop, struct sprite
    *ennemie)
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
        if (event.type == sfEvtKeyPressed || event.key.code == sfKeyEscape)
            usoop->pause = 1;
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

static void event_pause(sfRenderWindow *window, struct sprite *background,
    struct sprite *usoop)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed) {
            sfRenderWindow_close(window);
            usoop->pause = 0;
        }
        if (event.type == sfEvtKeyReleased && event.key.code == sfKeyEscape)
            usoop->pause = 0;
    }
}

static void pause_game(sfRenderWindow *window, struct sprite *background,
    struct sprite *usoop)
{
    sfTexture *texture = sfTexture_createFromFile("sprites/pause.png",
    NULL);
    sfSprite *sprite = sfSprite_create();

    sfSprite_setTexture(sprite, texture, sfTrue);
    sfRenderWindow_setMouseCursorVisible(window, sfTrue);
    sfSprite_setPosition(sprite, (sfVector2f){1500 / 2 - 150, 900 / 2 - 150});
    sfRenderWindow_clear(window, sfWhite);
    sfRenderWindow_drawSprite(window, sprite, NULL);
    sfRenderWindow_display(window);
    while (usoop->pause == 1) {
        event_pause(window, background, usoop);
    }
    sfRenderWindow_setMouseCursorVisible(window, sfFalse);
    return;
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
    if (usoop->pause == 1)
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

static void set_music(void)
{
    sfMusic *music = sfMusic_createFromFile("sound/weare.ogg");

    sfMusic_setLoop(music, sfTrue);
    sfMusic_setVolume(music, 10);
    sfMusic_play(music);
}

void game(sfRenderWindow *window, struct sprite *usoop,
    struct sprite *ennemie, struct sprite *background)
{
    while (sfRenderWindow_isOpen(window)) {
        pop_event(window, usoop, ennemie);
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
    set_music();
    set_perso(window, &usoop);
    set_ennemie(window, &ennemie);
    set_background(&background);
    sfRenderWindow_setMouseCursorVisible(window, sfFalse);
    game(window, &usoop, &ennemie, &background);
    cleanup(&usoop, &ennemie, &background);
    sfRenderWindow_destroy(window);
    return 0;
}
