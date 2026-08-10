#include <stdio.h>
#include <stdlib.h>

#include "mirror.h"
#include "path_builder.h"

int check_mirror_list(char *full_path)
{
    FILE *file = fopen(full_path, "r");

    if (!file)
    {
        perror("Erreur lors de l'ouverture de la base de données");
        return -1;
    }

    // On vérifie que le fichier ne soit pas vide
    int ch = fgetc(file);
    if (ch == EOF) {
        fclose(file);
        return -1; 
    }

    fclose(file);
    return 1;
}

int mirror_check(void)
{
    static const char *mirror_file = "mirror.txt"; 
    
    char *full_path = make_path(mirror_file);
    if (!full_path)
    {
        return -1;
    }

    if (check_mirror_list(full_path) != 1)
    {
        fprintf(stderr, "Erreur : Le fichier est vide, aucun mirroir renseigné!\nVeuillez ajouter un mirroir dans le fichier ~/.packx/mirror.txt\n");
        return -1;
    }

    printf("TOUT EST OK POUR LE MOMENT!\n");

    free(full_path);
    return 1;
}