/*
** EPITECH PROJECT, 2023
** start oft my hunter
** File description:
** start
*/

#include "include/my_hunter.h"

static int readme(int ac, char **argv)
{
    int fd;
    char str[10000];

    if (ac > 2)
        return 84;
    if (argv[1][0] == '-' && argv[1][1] == 'h') {
        fd = open("readme.txt", O_RDONLY);
        read(fd, str, 10000);
        my_putstr(str);
        close(fd);
        return 0;
    } else
        return 84;
}

void cleanup(struct sprite *usoop, struct sprite *ennemie, sprite
    *background)
{
    sfTexture_destroy(usoop->texture);
    sfSprite_destroy(usoop->sprite);
    sfClock_destroy(usoop->clock);
    sfMusic_destroy(usoop->music);
    sfText_destroy(usoop->score.text);
    sfRectangleShape_destroy(usoop->life.bar);
    sfRectangleShape_destroy(usoop->back_life.bar);
    sfTexture_destroy(ennemie->texture);
    sfSprite_destroy(ennemie->sprite);
    sfClock_destroy(ennemie->clock);
    sfTexture_destroy(background->texture);
    sfSprite_destroy(background->sprite);
    sfClock_destroy(background->clock);
}

int main(int ac, char **av)
{
    if (ac > 1)
        return readme(ac, av);
    return my_hunter();
}
