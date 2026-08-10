#include <stdio.h>
#include <stdlib.h>

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
