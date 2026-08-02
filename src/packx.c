#include <stdio.h>
#include <string.h>

// /include
#include "commands.h"

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
        printf("Mauvaise utilisation de la commande rex, tapez 'rex -h' pour obtenir de l'aide\n");
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