#ifndef _MAIN_H
#define _MAIN_H
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <dirent.h>
#include <stddef.h>
#include <string.h>

/**
 * struct path - singly linked list
 * @path: string - (malloc'ed string)
 * @next: points to the next node
 * Description: singly linked list node structure
 * for Shell project
 */
typedef struct path
{
	char *path;
	struct path *next;
} path_t;

int _strlen(char *s);
char *_strcpy(char *dest, char *src);
char *_strdup(char *str);
int _strcmp(char *s1, char *s2);
char *_strcat(char *dest, char *src);
