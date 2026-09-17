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

int packx_help(char *target_pkg)
{
    if (target_pkg == NULL)
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
    }else
    {
    
        if (pkg_installed(target_pkg) == 0)
        {
            printf("Aide demandé pour le paquet: %s\n", target_pkg);
            return 0;
        }
        
        printf("%s est introuvable, vérifiez qu'il soit bien installer\n", target_pkg);
    }
    return 0;
}