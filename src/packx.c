#include <stdio.h>
#include <string.h>

// /include
#include "commands.h"
#include "version.h"
#include "packx_color.h"

/** Main function.
 * @param argc
 * @param argv
 * @return A return code indicating success, failure, etc.
 */
int main(int argc, char *argv[])
{
    // On vérifie que le nombre d'arguments soit logique (au moins 2; ex : rex[0] install[2] htop[3])
    if (argc < 2)
    {
        printf("PACKX VERSION : %s\n", PACKX_V);
        printf("PACKX est un gestionnaire de paquets minimaliste conçu pour les distributions Linux en phase de développement (stade BLFS - Beyond Linux From Scratch).\nIl n'a pas pour vocation de concurrencer `apt`, `pacman`, `dnf` ou autres gestionnaires matures, mais offre une alternative simple et facile à intégrer pour les petites distributions en construction.\n");
        printf("\nTaper "WARNING"packx -h"NORMAL" pour afficher la listes des commandes disponible!\n");
        printf("\nDéveloppeur du projet :\n"SUCCES" Rudy DANIEL - @WXXDEN"NORMAL);
        return 1;
    }
    
    for (int i = 0; commands[i].name != NULL; i++)
    {
        if (strcmp(argv[1], commands[i].name) == 0){
            return commands[i].func(argc, argv);
        }
    }

    printf("Commande inconnue: %s\n", argv[1]);
    
    return 1;   
}