/*
** EPITECH PROJECT, 2023
** pause menu
** File description:
** menu pause
*/
#include "include/my_hunter.h"

static void pause_sound(struct sprite *background, sfEvent event, sfSprite
    *sprite_soundon, sfSprite *sprite_soundoff)
{
    int mouseX = event.mouseButton.x;
    int mouseY = event.mouseButton.y;
    sfFloatRect spriteBoundson = sfSprite_getGlobalBounds(sprite_soundon);
    sfFloatRect spriteBoundsoff = sfSprite_getGlobalBounds(sprite_soundoff);

    if (event.mouseButton.button == sfMouseLeft) {
        if (sfFloatRect_contains(&spriteBoundson, mouseX, mouseY))
            sfMusic_play(background->music);
        if (sfFloatRect_contains(&spriteBoundsoff, mouseX, mouseY))
            sfMusic_pause(background->music);
    }
}

static void event_pause(sfRenderWindow *window, struct sprite *background,
    sfSprite *sprite_soundon, sfSprite *sprite_soundoff)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed) {
            sfRenderWindow_close(window);
            background->pause = 0;
        }
        if (event.type == sfEvtKeyReleased && event.key.code == sfKeyEscape)
            background->pause = 0;
        if ( (event.type == sfEvtKeyPressed || event.type ==
        sfEvtMouseButtonPressed) && event.mouseButton.button == sfMouseLeft)
            pause_sound(background, event, sprite_soundon, sprite_soundoff);
    }
}

static void set_pause(sfRenderWindow *window, sfSprite *sprite, sfSprite
    *sprite_sound, sfSprite *sprite_soundon)
{
    sfRenderWindow_setMouseCursorVisible(window, sfTrue);
    sfSprite_setScale(sprite_sound, (sfVector2f){0.3, 0.3});
    sfSprite_setScale(sprite_soundon, (sfVector2f){0.3, 0.3});
    sfSprite_setPosition(sprite, (sfVector2f){1500 / 2 - 150, 900 / 2 - 150});
    sfSprite_setPosition(sprite_sound, (sfVector2f){10, 700});
    sfSprite_setPosition(sprite_soundon, (sfVector2f){10, 800});
    sfRenderWindow_clear(window, sfWhite);
    sfRenderWindow_drawSprite(window, sprite, NULL);
    sfRenderWindow_drawSprite(window, sprite_sound, NULL);
    sfRenderWindow_drawSprite(window, sprite_soundon, NULL);
    sfRenderWindow_display(window);
}

static void clean_text(sfTexture *texture, sfTexture *texture_soundoff,
    sfTexture *texture_soundon)
{
    sfTexture_destroy(texture);
    sfTexture_destroy(texture_soundoff);
    sfTexture_destroy(texture_soundon);
}

static void clean_sprite(sfSprite *sprite, sfSprite *sprite_soundon, sfSprite
    *sprite_soundoff)
{
    sfSprite_destroy(sprite);
    sfSprite_destroy(sprite_soundoff);
    sfSprite_destroy(sprite_soundon);
}

void pause_game(sfRenderWindow *window, struct sprite *background,
    struct sprite *usoop)
{
    sfTexture *texture = sfTexture_createFromFile("sprites/pause.png", NULL);
    sfSprite *sprite = sfSprite_create();
    sfTexture *texture_soundoff = sfTexture_createFromFile
    ("sprites/soundoff.png", NULL);
    sfSprite *sprite_soundoff = sfSprite_create();
    sfTexture *soundon = sfTexture_createFromFile("sprites/sound.png", NULL);
    sfSprite *sprite_soundon = sfSprite_create();

    sfSprite_setTexture(sprite, texture, sfTrue);
    sfSprite_setTexture(sprite_soundoff, texture_soundoff, sfTrue);
    sfSprite_setTexture(sprite_soundon, soundon, sfTrue);
    set_pause(window, sprite, sprite_soundoff, sprite_soundon);
    while (background->pause == 1)
        event_pause(window, background, sprite_soundon, sprite_soundoff);
    clean_sprite(sprite, sprite_soundon, sprite_soundoff);
    clean_text(texture, texture_soundoff, soundon);
    sfRenderWindow_setMouseCursorVisible(window, sfFalse);
    return;
}
