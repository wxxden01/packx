#include <string.h>
#include <stdio.h>

#include "commands.h"
#include "help.h"
#include "search_packx.h"
#include "version.h"

// TEMPORAIRE
int packx_install(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    printf("Test ok!\n");

    return 0;
}

int packx_remove(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    printf("Test ok!\n");

    return 0;

}

int packx_update(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    printf("Test ok!\n");

    return 0;
}


command_packx commands[] = {
    {"install", packx_install, "Installer un paquet"},
    {"remove",  packx_remove,  "Supprimer un paquet"},
    {"search",  packx_search,  "Rechercher un paquet"},
    {"update",  packx_update,  "Mettre à jour"},
    {"-h",      packx_help,    "Afficher l'aide de Packx ou d'un paquet"},
    {"-v",      packx_version, "Donne le nuémro de version de Packx ou d'un paquet"},
    {NULL, NULL, NULL}
};