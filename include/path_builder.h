#ifndef PATH_BUILDER_H
#define PATH_BUILDER_H
/**
 * @brief Construit le chemin vers une ressource
 * @param path chemin vers la ressource
 * @param file_name Nom du fichier vers lequel on veut pointer
 * @return Renvoie le chemin complet
 */
char *generate_path(const char *path, const char *file_name);
#endif