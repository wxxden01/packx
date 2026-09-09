#ifndef CHECK_HASH_H
#define CHECK_HASH_H

/**
 * @brief Génère le hash SHA256 d'un fichier donné
 * @param pkg_name nom de paquet
 * @param output_path Hash génèrer en sortie
 * @return 0 et output_path en cas de succés et 1 en cas contraire
 */
int hash_generator_SHA256(char *pkg_name, char *output_hash);

/**
 * @brief Récupère le hash de la fonction `make_hash_SHA256()` et le compare au hash de référence en bdd
 * @param pkg_name Nom du paquet que l'on souhaite vérifier
 * @return 0 pour succés, -1 pour échec
 */
int check_SHA256(char *pkg_name, char *pkg_hash);

#endif