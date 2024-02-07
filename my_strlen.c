/*
** EPITECH PROJECT, 2023
** MY STRLEN
** File description:
** give the length of a str
*/
#include "include/my_hunter.h"

int my_strlen(char const *str)
{
    int index;
    int compt;

    compt = 0;
    for ( index = 0; str[index] != '\0'; index++) {
        compt++;
    }
    return compt;
}
