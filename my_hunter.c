/*
** EPITECH PROJECT, 2023
** start oft my hunter
** File description:
** start
*/

#include "include/my_hunter.h"

const char *files_nico[] = {
    "./sound/weare.ogg",
    "./sound/roblox.wav",
    "./end.png",
    "./ruche.jpg",
    "./sprites/usooprun.png",
    "./sprites/gearfourth.png",
    "./sprites/doflamingo.png",
    "./sprites/target.png",
    "./sprites/sound.png",
    "./sprites/pause.png",
    "./sprites/projectile.png",
    "./sprites/die.png",
    "./sprites/fireusoop.png",
    "./sprites/logo.png",
    "./sprites/barbenoir.png",
    "./sprites/cursor.png",
    "./sprites/luffyfire.png",
    "./sprites/dure.png",
    "./sprites/logo_marine.png",
    "./sprites/soundoff.png",
    "./sprites/bras.png",
    "./sprites/luccirun.png",
    "./dressrosa.png",
    "./font/arial.ttf",
    "./map.png"
};

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

static void cleanup_end(struct sprite *usoop, struct sprite *ennemie, sprite
    *background)
{
    sfClock_destroy(ennemie->clock);
    sfTexture_destroy(ennemie->proj.texture);
    sfSprite_destroy(ennemie->proj.sprite);
    sfTexture_destroy(background->texture);
    sfSprite_destroy(background->sprite);
    sfClock_destroy(background->clock);
    sfTexture_destroy(background->cursor.texture);
    sfSprite_destroy(background->cursor.sprite);
    sfTexture_destroy(background->proj.texture);
    sfSprite_destroy(background->proj.sprite);
}

void cleanup(struct sprite *usoop, struct sprite *ennemie, sprite
    *background)
{
    sfTexture_destroy(usoop->texture);
    sfSprite_destroy(usoop->sprite);
    sfTexture_destroy(usoop->cursor.texture);
    sfSprite_destroy(usoop->cursor.sprite);
    sfTexture_destroy(usoop->proj.texture);
    sfSprite_destroy(usoop->proj.sprite);
    sfClock_destroy(usoop->clock);
    if (usoop->score.text != NULL)
        sfText_destroy(usoop->score.text);
    sfRectangleShape_destroy(usoop->life.bar);
    sfRectangleShape_destroy(usoop->back_life.bar);
    sfTexture_destroy(ennemie->texture);
    sfSprite_destroy(ennemie->sprite);
    cleanup_end(usoop, ennemie, background);
}

static int verify_assets(void)
{
    int fd;

    for (int i = 0; i < 25; i++) {
        fd = open(files_nico[i], O_RDONLY);
        if (fd == -1)
            return 84;
        if (close(fd) == -1)
            return 84;
    }
    return 0;
}

static int my_strcmp_for_hunter(char *s1, char *s2)
{
    for (int i = 0; s1[i] != '\0' && s2[i] != '\0'; i++) {
        if (s1[i] != s2[i])
            return 1;
    }
    return 0;
}

static int check_env(char **env)
{
    for (int i = 0; env[i]; i++) {
        if (my_strcmp_for_hunter(env[i], "DISPLAY=") == 0)
            return 0;
    }
    return 84;
}

int main(int ac, char **av, char **env)
{
    if (check_env(env) == 84)
        return 84;
    if (ac > 1)
        return readme(ac, av);
    if (verify_assets() == 84)
        return 84;
    return my_hunter();
}

void new_highscore(char *buffer, struct sprite *background, struct
    sprite *usoop, int fd)
{
    int ca;
    int len;

    my_strcat(buffer, int_to_str(background->score.min));
    my_strcat(buffer, ":");
    my_strcat(buffer, int_to_str(background->score.sec));
    ca = open("high_score.txt", O_RDWR | O_TRUNC);
    write(ca, buffer, my_strlen(buffer));
    close(ca);
    sfText_setString(usoop->score.text, buffer);
    free(buffer);
    close(fd);
}
