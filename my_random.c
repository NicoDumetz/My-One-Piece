/*
** EPITECH PROJECT, 2023
** return random number
** File description:
** func with time return random num
*/
#include "include/my_hunter.h"
#include <fcntl.h>

int my_random(int min, int max)
{
    int a;
    int fd;
    int compt;

    fd = open("/dev/urandom", O_RDONLY);
    read(fd, &a, sizeof(int));
    a = a < 0 ? a * -1 : a;
    a = a % (max - min) + min;
    close(fd);
    return a;
}
