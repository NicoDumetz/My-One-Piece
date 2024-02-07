/*
** EPITECH PROJECT, 2023
** final
** File description:
** final scene
*/
#include "include/my_hunter.h"

void check_death_gear(struct sprite *ennemie, sfEvent event, sfRenderWindow
    *window, struct sprite *usoop)
{
    int mouseX = event.mouseButton.x;
    int mouseY = event.mouseButton.y;
    sfFloatRect spriteBounds = sfSprite_getGlobalBounds(ennemie->sprite);

    ennemie->cursor.pos.x = mouseX - (118 / 2);
    ennemie->cursor.pos.y = mouseY - (117 / 2);
    if (sfFloatRect_contains(&spriteBounds, mouseX, mouseY)) {
            ennemie->touch = 1;
            ennemie->cursor.bo = 1;
            sfClock_restart(ennemie->cursor.clock);
            sfSprite_setPosition(ennemie->cursor.sprite, ennemie->cursor.pos);
            sfClock_restart(ennemie->proj.clock);
            sfSprite_setPosition(ennemie->proj.sprite, ennemie->proj.pos);
            ennemie->life.size.x -= 10;
            sfRectangleShape_setSize(ennemie->life.bar, ennemie->life.size);
    }
}

static void fly_gear(struct sprite *usoop)
{
    sfTime elapsed = sfClock_getElapsedTime(usoop->clock);

    if (sfTime_asSeconds(elapsed) >= 0.2) {
        sfClock_restart(usoop->clock);
        if (usoop->compt == 9) {
            usoop->compt = 7;
            usoop->rect.left = 7 * usoop->rect.width;
        } else
            usoop->rect.left += usoop->rect.width;
        sfSprite_setTextureRect(usoop->sprite, usoop->rect);
        usoop->compt++;
    }
}

void fly_luffy(struct sprite *usoop)
{
    if (usoop->compt < 7) {
        usoop->compt = 8;
        usoop->rect.left = 7 * usoop->rect.width + 7;
        usoop->rect.width = 310;
        usoop->rect.height = 216 * 2;
        usoop->rect.top = 100;
        usoop->scale.x = 2;
        usoop->pos.x = 750;
        sfSprite_setPosition(usoop->sprite, usoop->pos);
        sfSprite_setScale(usoop->sprite, usoop->scale);
        sfSprite_setTextureRect(usoop->sprite, usoop->rect);
    }
    usoop->pos.x -= 2;
    usoop->pos.y -= 4;
    if (usoop->pos.y <= -850)
        usoop->bo = 8;
    sfSprite_setPosition(usoop->sprite, usoop->pos);
    fly_gear(usoop);
}

void big_fist(struct sprite *usoop)
{
    if (usoop->compt < 18) {
        usoop->compt = 18;
        usoop->rect.left = 18 * usoop->rect.width - 100;
        usoop->rect.width = 350;
        usoop->rect.height = 216 * 2.31;
        usoop->rect.top = 0;
        usoop->scale.x = 2;
        usoop->pos.x = 100;
        usoop->pos.y = -1700;
        sfSprite_setPosition(usoop->sprite, usoop->pos);
        sfSprite_setScale(usoop->sprite, usoop->scale);
        sfSprite_setTextureRect(usoop->sprite, usoop->rect);
    }
    usoop->pos.y += 4;
    if (usoop->pos.y >= -800)
        usoop->bo = 9;
    sfSprite_setPosition(usoop->sprite, usoop->pos);
}

void die_end(struct sprite *usoop, struct sprite *ennemie)
{
    sfTime elapsed = sfClock_getElapsedTime(usoop->clock);

    if (usoop->compt > 3) {
        ennemie->texture = sfTexture_createFromFile("sprites/die.png",
        NULL);
        usoop->compt = 0;
        ennemie->rect.left = 205 * 2;
        ennemie->rect.width = 205;
        ennemie->rect.height = 146;
        ennemie->rect.top = 0;
        ennemie->pos.y = 500;
        sfClock_restart(usoop->clock);
        sfSprite_setPosition(ennemie->sprite, ennemie->pos);
        sfSprite_setTexture(ennemie->sprite, ennemie->texture, sfTrue);
        sfSprite_setTextureRect(ennemie->sprite, ennemie->rect);
        sfSprite_setTextureRect(ennemie->sprite, ennemie->rect);
    }else if (sfTime_asSeconds(elapsed) >= 1.5 && usoop->win < 3)
        usoop->win = 2;
}

static void set_game_over(struct sprite *background, struct sprite
    *usoop)
{
    char buffer[100];

    background->texture = sfTexture_createFromFile("end.png", NULL);
    background->sprite = sfSprite_create();
    background->scale = (sfVector2f){1.8, 1.30};
    usoop->win = usoop->win == 1 ? 3 : 4;
    sfSprite_setTexture(background->sprite, background->texture, sfTrue);
    sfSprite_setScale(background->sprite, background->scale);
    sfText_setFillColor(background->score.text, sfWhite);
    buffer[0] = '\0';
    my_strcat(buffer, "Your score ");
    my_strcat(buffer, int_to_str(background->score.min));
    my_strcat(buffer, ":");
    my_strcat(buffer, int_to_str(background->score.sec));
    sfText_setString(background->score.text, buffer);
    sfText_setPosition(background->score.text, (sfVector2f){10, 10});
}

void end_game(sfRenderWindow *window, struct sprite *background, struct sprite
    *usoop)
{
    if (usoop->win == 1 || usoop->win == 2)
        set_game_over(background, usoop);
    sfRenderWindow_drawSprite(window, background->sprite, NULL);
    if (usoop->win == 4)
        sfRenderWindow_drawText(window, background->score.text, NULL);
    sfRenderWindow_display(window);
}
