#include "main.h"
/**
 * _strdup - char func
 * @str: param
 *
 * Return: pointer
 */
char *_strdup(char *str)
{
    int i;
    char *dest_str;

    if (str == NULL)
        return (NULL);
    for (i = 0; str[i] != '\0'; i++)
        ;
    dest_str = malloc(sizeof(char) * (i + 1));
    if (dest_str == NULL)
        return (NULL);
    for (i = 0; str[i] != '\0'; i++)
    {
        dest_str[i] = str[i];
    }
    dest_str[i] = '\0';
    return (dest_str);
}
/**
 * _splitstring - int func
 * @str: param
 *
 * Return: param
 */
int _splitstring(char *str)
{
    int i;
    int searchflag = 1;
    int wordcount = 0;

    for (i = 0; str[i]; i++)
    {
        if (str[i] != ' ' && searchflag == 1)
        {
            wordcount += 1;
            searchflag = 0;
        }
        if (str[i + 1] == ' ')
            searchflag = 1;
    }
    return (wordcount);
}
/**
 * _strcmp - int func
 * @s1: param
 * @s2: param
 * Return: int
 */
int _strcmp(const char *s1, const char *s2)
{
    while ((*s1 != '\0' && *s2 != '\0') && *s1 == *s2)
    {
        s1++;
        s2++;
    }
    if (*s1 == *s2)
        return (0);
    else
        return (*s1 - *s2);
}
/**
 * _strcat - char func
 * @dest: param
 * @src: param
 * i - param
 * j - param
 * Return: char
 */
char *_strcat(char *dest, char *src)
{
    int i;
    int j;

    for (i = 0; dest[i] != '\0'; i++)
        ;
    for (j = 0; src[j] != '\0'; j++, i++)
        dest[i] = src[j];
    dest[i] = '\0';
    return (dest);
}
/**
 * _strlen - int func
 * @s: param
 * i - param
 * Return: int
 */
int _strlen(char *s)
{
    int i;

    for (i = 0; s[i]; i++)
        ;
    return (i);
}
