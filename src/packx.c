#include <stdio.h>
#include <string.h>

// /include
#include "commands.h"
#include "has_sudo.h"
#include "version.h"
#include "packx_color.h"

/** Main function.
 * @param argc
 * @param argv
 * @return A return code indicating success, failure, etc.
 */
int main(int argc, char *argv[])
{
    // On vérifie que le nombre d'arguments soit logique (au moins 2; ex : packx[0] install[1] btop[2])
    if (argc == 1)
    {
        printf("PACKX VERSION : %s\n", PACKX_V);
        printf("PACKX est un gestionnaire de paquets minimaliste conçu pour les distributions Linux en phase de développement (stade BLFS - Beyond Linux From Scratch).\nIl n'a pas pour vocation de concurrencer `apt`, `pacman`, `dnf` ou autres gestionnaires matures, mais offre une alternative simple et facile à intégrer pour les petites distributions en construction.\n");
        printf("\nTaper "WARNING"packx -h"NORMAL" pour afficher la listes des commandes disponible!\n");
        printf("\nDéveloppeur du projet :\n"SUCCES" Rudy DANIEL - @WXXDEN"NORMAL);
        return 1;
    }else
    {
        // On récupère la commande
        char command[64] = {0};
        // On récupère le pkg si renseigné
        char pkg_selected[64] = {0};
        snprintf(pkg_selected, sizeof(pkg_selected), "%s", argv[2]);

        // Appeller la fonction associé
        snprintf(command, sizeof(command), "%s", argv[1]);
         for (int i = 0; commands[i].name != NULL; i++)
        {
            if (strcmp(command, commands[i].name) == 0){
                return commands[i].func(pkg_selected);
            }
        }
        printf("Commande %s introuvable!\n", argv[1]);
    }

    return 0;   
}