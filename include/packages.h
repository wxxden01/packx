#ifndef PACKAGES_H
#define PACKAGES_H
#include <stdbool.h>

typedef struct {
    char name[64];
    char version[16];
    char size[16];
} package_t;

/**
 * @brief Récupère et parse d'une ligne selon un format précis
 * @param line Ligne envoyé par la fonctions db_pkg_reader()
 * @param pkg Nom du paquet
 * @return Renvoie un tableau avec les différentes informations du paquet (nom|version|taille)
 */
int parse_line(const char *line, package_t *pkg);

/**
 * @brief Lit un fichier et appelle la fonction parse_line() pour chaque ligne à la recherche du paquet demandé
 * @param filepath Chemin vers le fichier
 * @param target_pkg Le paquet demandé
 * @return Renvoie les informations du paquet
 */
int db_pkg_reader(const char *filepath, const char *target_pkg);

#endif 