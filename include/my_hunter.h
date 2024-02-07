/*
** EPITECH PROJECT, 2023
** include
** File description:
** header myhunter
*/

#ifndef MY_LS
    #define MY_LS
    #include <errno.h>
    #include <dirent.h>
    #include <sys/stat.h>
    #include <time.h>
    #include <pwd.h>
    #include <grp.h>
    #include <errno.h>
    #include <string.h>
    #include <SFML/Audio.h>
    #include <SFML/Graphics.h>
    #include <SFML/Window.h>
    #include <SFML/Graphics/Rect.h>
    #include <unistd.h>
    #include <time.h>
    #include <math.h>
    #include <stdlib.h>
    #include <fcntl.h>
    #include <unistd.h>
    #define PI 3.14159265358979323846

typedef struct chrono {
    int min;
    int sec;
    sfText *text;
} chrono;
typedef struct health {
    sfRectangleShape *bar;
    sfVector2f size;
    sfVector2f pos;
} health;
typedef struct cursor {
    sfTexture *texture;
    sfSprite *sprite;
    sfVector2f pos;
    sfVector2f scale;
    sfClock *clock;
    int bo;
    int act;
    sfVector2i mousepos;
    float angle;
} cursor;
typedef struct sprite {
    sfTexture *texture;
    sfSprite *sprite;
    sfVector2f pos;
    sfVector2f scale;
    sfIntRect rect;
    sfClock *clock;
    int compt;
    cursor cursor;
    cursor proj;
    int kill;
    int speed;
    char perso;
    sfMusic *music;
    int touch;
    int bo;
    health life;
    health back_life;
    chrono score;
    int win;
    int pause;
} sprite;
void animation_fire(sfRenderWindow *window, struct sprite *usoop);
void animation_walk(sfRenderWindow *window, struct sprite *usoop);
void animation(sfRenderWindow *window, struct sprite *usoop,
    struct sprite *ennemie);
void set_fire(sfRenderWindow *window, struct sprite *usoop);
void set_perso(sfRenderWindow *window, struct sprite *usoop);
void set_fire(sfRenderWindow *window, struct sprite *usoop);
void set_ennemie(sfRenderWindow *window, struct sprite *ennemie);
void animation_ennemie(sfRenderWindow *window, struct sprite *ennemie,
    struct sprite *usoop);
int my_random(int min, int max);
void check_death(struct sprite *ennemie, sfEvent event,
    sfRenderWindow *window, struct sprite *usoop);
void respawn_ennemie(struct sprite *ennemie);
void change_skin(struct sprite *usoop, struct sprite *ennemie);
void calculate_coord_proj(sfRenderWindow *window, struct sprite *usoop,
    struct sprite *ennemie);
void set_background(struct sprite *background);
void display_background(sfRenderWindow *window, struct sprite *background,
    struct sprite *ennemie);
void set_pos_cursor(struct sprite *usoop, sfRenderWindow *window);
void gearth_fourth(struct sprite *usoop, struct sprite *ennemie);
void set_life_perso(struct sprite *usoop);
void set_life_ennemie(struct sprite *ennemie);
void check_death_gear(struct sprite *ennemie, sfEvent event, sfRenderWindow
    *window, struct sprite *usoop);
void fly_luffy(struct sprite *usoop);
void big_fist(struct sprite *usoop);
void die_end(struct sprite *usoop, struct sprite *ennemie);
int my_getnbr(char const *str);
char *my_strcat(char *dest, char const *src);
int my_strlen(char const *str);
char *int_to_str(int nb);
void end_game(sfRenderWindow *window, struct sprite *background, struct sprite
    *usoop);
int my_putstr(char const *str);
int my_hunter(void);
void cleanup(struct sprite *usoop, struct sprite *ennemie, sprite
    *background);


#endif
