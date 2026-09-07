#include <stdio.h>
#include <stdlib.h>

#include "path.h"
#include "paths.h"

#define PATH_MAX_LEN 256

char *make_path(const char *path)
{
    const char *home = getenv("HOME");
    if (!home) {
        fprintf(stderr, "Erreur : Impossible de récupérer la variable $HOME.\n");
        return NULL;
    }

    // Allocation de la mémoire
    char *full_path = malloc(PATH_MAX_LEN);
    if (!full_path) {
        perror("Erreur d'allocation mémoire");
        return NULL;
    }

    int written = snprintf(full_path, PATH_MAX_LEN, "%s/.packx/%s", home, path);
    if (written < 0 || written >= PATH_MAX_LEN) {
        fprintf(stderr, "Erreur : Le chemin généré est trop long.\n");
        free(full_path); // Évite une fuite mémoire si le chemin dépasse 255 caractères
        return NULL;
    }

    return full_path;
}

char *generate_path(const char *path, const char *file_name)
{
    size_t len = snprintf(NULL, 0, "%s/%s", path, file_name) + 1;
    char *generated_path = malloc(len);
    if (generated_path == NULL) {
        return NULL;
    }
    snprintf(generated_path, len, "%s/%s", path, file_name);
    return generated_path;
}