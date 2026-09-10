#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "help.h"
#include "has_sudo.h"
#include "version.h"
#include "packages.h"
#include "commands.h"
#include "packx_color.h"

#define PATH_MAX_LEN 256

int packx_help(int argc, char **argv)
{
    if ((sudo(argv[0]) && argc <4) || (!sudo(argv[0]) && argc < 3))
    {
        printf("%s", PACKX_VERSION);
        printf("PACKX est un gestionnaire de paquet en ligne de commande!\n\n");
        printf(BOLD"Liste des commandes disponible pour packx:\n"NORMAL);

        for (size_t i  = 0; commands[i].name != NULL; i++) {
            printf("  %-26s %s\n",
                commands[i].name,
                commands[i].desc);
        }

        printf("\nDéveloppeurs du projet : \n Rudy DANIEL - @WXXDEN\n");
    }
    else if ((sudo(argv[0]) && argc > 4) || (!sudo(argv[0]) && argc > 3))
    {
        printf("Mauvaise utilisation de la commande 'help'\nUtilisation : packx -h <pkg>\n");
    }
    
    else{
        char pkg_selected[256];

        // Check if argc has enough elements before accessing argv
        if (sudo(argv[0])) {
            strncpy(pkg_selected, argv[3], sizeof(pkg_selected) - 1);
            pkg_selected[sizeof(pkg_selected) - 1] = '\0';
        } else {
            strncpy(pkg_selected, argv[2], sizeof(pkg_selected) - 1);
            pkg_selected[sizeof(pkg_selected) - 1] = '\0';
        }
    
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