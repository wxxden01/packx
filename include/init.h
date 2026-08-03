#ifndef INIT_H
#define INIT_H

// Types d'entrées à vérifier
typedef enum {
    ENTRY_DIR,
    ENTRY_FILE
} EntryType;

// Structure de l'arbo
typedef struct
{
    const char *rel_path;
    EntryType type;
} SchemaEntry;

/**
 * @brief Construit le chemin complet et créer le répertoire / fichier si non créer
 * @param base_dir répertoire de base de Packx
 * @param entry arborescence (struct)
 * @return Succés ou erreur
 */
int check_or_create_entry(const char *base_dir, const SchemaEntry *entry);

/**
 * @brief Vérifie et créer l'arborescence si nécessaire 
 * @param void
 * @return Succés ou erreur
 */
int init_packx(void);

#endif