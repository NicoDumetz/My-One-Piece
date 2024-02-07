/*
** EPITECH PROJECT, 2023
** my_intlen
** File description:
** give the length of an int
*/
#include "include/my_hunter.h"

int my_intlen(long nb)
{
    int compt = 0;

    if ( nb < 0 ) {
        nb = nb * -1;
        compt++;
    }
    if (nb == 0)
        return compt + 1;
    for (int i; nb > 0; i++) {
        compt++;
        nb /= 10;
    }
    return compt;
}
