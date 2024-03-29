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
    sfVector2u windowSize = sfRenderWindow_getSize(window);
    float scale_X = (float)windowSize.x / 1500;
    float scale_Y = (float)windowSize.y / 900;
    int mouseX = event.mouseButton.x / scale_X;
    int mouseY = event.mouseButton.y / scale_Y;
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

static void set_highscore(char *buffer, char *str, struct sprite *usoop, int
    fd)
{
    sfText_setString(usoop->score.text, str);
    free(buffer);
    free(str);
    close(fd);
}

static void get_high(struct sprite *usoop, struct sprite *background)
{
    int fd;
    char *str = malloc(100);
    char *buffer = malloc(100);
    int min;
    int sec;
    int fin;

    buffer[0] = '\0';
    my_strcat(buffer, "Best Score ");
    fd = open("high_score.txt", O_RDWR);
    fin = read(fd, str, 100);
    str[fin] = '\0';
    min = my_getnbr(str + 11);
    sec = my_getnbr(str + (my_intlen(my_getnbr(str)) + 12));
    if ((min == 0 && sec == 0) || ( min > background->score.min || (min ==
        background->score.min && sec > background->score.sec) ))
        return new_highscore(buffer, background, usoop, fd);
    if (min < background->score.min || (min == background->score.
        min && sec < background->score.sec))
        return set_highscore(buffer, str, usoop, fd);
}

static void set_best_score(struct sprite *usoop, struct sprite *background)
{
    sfFont* font = sfFont_createFromFile("font/arial.ttf");

    usoop->score.text = sfText_create();
    sfText_setFont(usoop->score.text, font);
    sfText_setCharacterSize(usoop->score.text, 30);
    sfText_setPosition(usoop->score.text, (sfVector2f){10, 100});
    sfText_setFillColor(usoop->score.text, sfWhite);
    sfSprite_setTexture(usoop->sprite, usoop->texture, sfTrue);
    get_high(usoop, background);
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
    if (usoop->win == 4) {
        my_strcat(buffer, "Your score ");
        my_strcat(buffer, int_to_str(background->score.min));
        my_strcat(buffer, ":");
        my_strcat(buffer, int_to_str(background->score.sec));
        sfText_setString(background->score.text, buffer);
        sfText_setPosition(background->score.text, (sfVector2f){10, 10});
        set_best_score(usoop, background);
    }
}

void end_game(sfRenderWindow *window, struct sprite *background, struct sprite
    *usoop)
{
    if (usoop->win == 1 || usoop->win == 2)
        set_game_over(background, usoop);
    sfRenderWindow_drawSprite(window, background->sprite, NULL);
    if (usoop->win == 4) {
        sfRenderWindow_drawText(window, background->score.text, NULL);
        sfRenderWindow_drawText(window, usoop->score.text, NULL);
    }
    sfRenderWindow_display(window);
}
