#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mirror.h"
#include "path_builder.h"
#include "packages.h"

#define PATH_MAX_LEN 256

// Vérifie qu'au moins un mirroir est définit
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
    return 0;
}

// choisir le mirroir à partir de la liste des mirroirs définit
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
        size_t len = strlen(line);
        // Enlève le retour à la ligne
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
        found_line = strdup(line);
        break;
    }

    fclose(file);
    return found_line;
}

// Vérifier que le paquet est disponible sur le mirroir
int download_mirror_db(const char *mirror)
{
    // Construction du chemin vers le repo du miroir
    static char db_path[PATH_MAX_LEN];
    snprintf(db_path, sizeof(db_path), "%s/%s", mirror, "repo.db");
    
    // Construction du chemin vers le cache
    const char *dir_name = "cache/repo.db";
    char *cache_path = make_path(dir_name);
    if (!cache_path)
    {
        return -1;
    }

    // Construction de la ommande
    char command[512];
    snprintf(command, sizeof(command), "curl -s \"%s\" -o \"%s\"", db_path, cache_path);
    // Exécution de la commande construite
    int status = system(command);
    
    // Vérification de la bonne exécution
    if (status != 0) {
        fprintf(stderr, "Erreur lors du téléchargement de la base de données.\n");
        return -1;
    }
    
    return 0;
}

int mirror_check(void)
{
    static const char *mirror_file = "mirror.txt"; 
    
    char *full_path = make_path(mirror_file);
    if (!full_path)
    {
        return -1;
    }

    if (check_mirror_list(full_path) != 0)
    {
        fprintf(stderr, "Erreur : Le fichier est vide, aucun mirroir renseigné!\nVeuillez ajouter un mirroir dans le fichier ~/.packx/mirror.txt\n");
        return -1;
    }

    char *mirror = select_mirror(full_path);
    if (mirror == NULL)
    {
        return -1;
    }

    if (!download_mirror_db(mirror))
    {
        return -1;
    }
    
    
    free(full_path);
    free(mirror);
    
    return 0;
}