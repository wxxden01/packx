#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

char *select_mirror(const char *file_name)
{
    FILE *file = fopen(file_name, "r");
    if (!file) {
        perror("Erreur lors de l'ouverture de la base de données");
        return NULL;
    }

    char line[256];
    char *found_line = NULL;

    while (fgets(line, sizeof(line), file)) {
        found_line = strdup(line);
        break;
    }

    fclose(file);
    return found_line;
}

// int pkg_found()
// {
//     char *repo_file = "repo.db";
// }

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


    char *mirror = select_mirror(full_path);
    if (mirror == NULL)
    {
        return -1;
    }

    free(full_path);
    free(mirror);

    return 1;
}