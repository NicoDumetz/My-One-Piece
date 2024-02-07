/*
** EPITECH PROJECT, 2023
** my_strcat
** File description:
** concatenate the second string into the first one
*/
#include "include/my_hunter.h"

char *my_strcat(char *dest, char const *src)
{
    int index;
    int len = my_strlen(dest);

    for ( index = 0; src[index]; index++) {
        dest[len] = src[index];
        len++;
    }
    dest[len] = '\0';
    return dest;
}
