#ifndef COMMANDS_H
#define COMMANDS_H

typedef struct
{
    const char *name;
    int (*func)(int, char **);
    const char *desc;
} command_packx;

// tableau des commandes associé à leurs fonctions
extern command_packx commands[];

#endif