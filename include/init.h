#ifndef INIT_H
#define INIT_H

int is_dir(const char *chemin);

/**
 * @brief Créer le répertoire source si non présent.
 * @param dir Chemin du répertoire
 * @return Erreur en cas d'échec, confirmation en cas de création du répertoire
 */
int init_source_dir(const char *dir);

/**
 * @brief Créer le fichier de bdd si non présent.
 * @param file chemin + nom du fichier.
 * @return erreur en cas d'échec.
 */
int init_db(const char *file);

/**
 * @brief Vérifie l'intégrité de Packx
 * @return 1 si un processus echoue, 0 si tout c'est bien passé
 */
int init_packx(void);

#endif