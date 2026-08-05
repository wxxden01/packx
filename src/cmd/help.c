#include <stdio.h>
#include <stdlib.h>

#include "version.h"
#include "packages.h"
#include "commands.h"

#define PATH_MAX_LEN 256

int packx_help(int argc, char **argv)
{
    if (argc < 3)
    {
        printf("%s", PACKX_VERSION);
        printf("PACKX est un gestionnaire de paquet en ligne de commande!\n\n");
        printf("Liste des commandes disponible pour rex:\n\n");

        for (size_t i  = 0; commands[i].name != NULL; i++)
        {
            printf(" %s - %s\n", commands[i].name, commands[i].desc);
        }
        
        // Ancienne version 
        // printf(" -h                - Sans argument, affiche la liste des commandes disponible; Suivit d'un argument (nom de paquet), les détailles de ce dernier seront affichés.\n");
        // printf(" install <package> - Installe le paquet demandé.\n");
        // printf(" remove <package>  - Supprime le paquet demandé.\n");
        // printf(" update            - Sans argument, met à jour le système complet; Suivit d'un argument (nom de paquet), ce dernier sera mit à jour.\n");

        printf("\nDéveloppeurs du projet : \nRudy DANIEL - @WXXDEN\nYmad Eddine HASSIN-BOUKAL - @zanblue\n");
    }
    else{
        const char *home = getenv("HOME");
        if (!home) return -1;

        char db_file[PATH_MAX_LEN];
        snprintf(db_file, sizeof(db_file), "%s/.packx/installed.db", home);

        if (db_pkg_reader(db_file, argv[2]) == 0)
        {
            printf("Aide demandé pour le paquet: %s\n", argv[2]);
            return 0;
        }
        
        printf("%s est introuvable, vérifiez qu'il soit bien installer\n", argv[2]);
    }
    return 0;
}