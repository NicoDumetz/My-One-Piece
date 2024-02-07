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

int main(int ac, char **av)
{
    if (ac > 1)
        readme(ac, av);
    return my_hunter();
}
