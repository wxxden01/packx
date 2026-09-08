#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "version.h"
#include "packages.h"
#include "commands.h"

#define PATH_MAX_LEN 256

int packx_help(int argc, char **argv)
{
    char pkg_selected[256];

    // Check if argc has enough elements before accessing argv
    if (argc > 0 && strcmp(argv[0], "sudo") == 0) {
        if (argc > 3) {
            strncpy(pkg_selected, argv[3], sizeof(pkg_selected) - 1);
            pkg_selected[sizeof(pkg_selected) - 1] = '\0';
        }
    } else {
        if (argc > 2) {
            strncpy(pkg_selected, argv[2], sizeof(pkg_selected) - 1);
            pkg_selected[sizeof(pkg_selected) - 1] = '\0';
        }
    }

    if (*pkg_selected == 3 && argc < 3)
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

        printf("\nDéveloppeurs du projet : \nRudy DANIEL - @WXXDEN\n");
    }
    else{
        package_t pkg;
        if (pkg_finder(1, pkg_selected, &pkg) == 0)
        {
            printf("Aide demandé pour le paquet: %s\n", pkg_selected);
            return 0;
        }
        
        printf("%s est introuvable, vérifiez qu'il soit bien installer\n", pkg_selected);
    }
    return 0;
}