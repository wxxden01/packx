#ifndef MIRROR_H
#define MIRROR_H

/**
 * @brief Vérifie que le fichier n'est pas vide
 * @param full_path Chemin vers le fichier
 * @return Retourne -1 si le fichier est vide et 1 en cas contraire
 */
int check_mirror_list(char *full_path);

int mirror_check(void);

char *select_mirror(const char *file_name);

// temp
// Callback appelé par libcurl à chaque chunk reçu
size_t write_to_file(void *contents, size_t size, size_t nmemb, void *userp);

int download_from_mirror(const char *mirror, const char *file_name);

#endif