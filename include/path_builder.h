#ifndef PATH_BUILDER_H
#define PATH_BUILDER_H
/**
 * @brief Construit le chemin vers une ressource
 * @param path chemin vers la ressource
 * @return Renvoie le chemin complet
 */
char *make_path(const char *path);


char *generate_path(const char *path, const char *file_name);
#endif