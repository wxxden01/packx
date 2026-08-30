#ifndef MIRROR_H
#define MIRROR_H

/**
 * @brief Vérifie que le fichier n'est pas vide
 * @param full_path Chemin vers le fichier
 * @return Retourne -1 si le fichier est vide et 1 en cas contraire
 */
int check_mirror_list();

/**
 * @brief Sélectionne un miroir dans la liste
 * @return Retourn une chaine avec le l'url ou NULL en cas d'échec
*/
char *select_mirror();

// temp
// Callback appelé par libcurl à chaque chunk reçu
size_t write_to_file(void *contents, size_t size, size_t nmemb, void *userp);

/**
 * @brief Télécharge une archive
 * @param mirror Nom du miroir à utiliser
 * @param file_name Archive à télécharger
 */
int download_from_mirror(const char *mirror, const char *file_name);

/**
 * @brief Réalise une série de testes pour pouvoir établire une connection au miroir
 * @return retourne 0 en cas de succés et -1 en cas d'erreur
 */
int mirror_check(void);


#endif