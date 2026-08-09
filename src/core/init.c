#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#include "init.h"

#define PATH_MAX_LEN 256

// Répertoir et fichier
static const SchemaEntry EXPECTED_STRUCTURE[] = {
    {"", ENTRY_DIR},
    {"db", ENTRY_DIR},
    {"installed.db", ENTRY_FILE},
    {"mirror.txt", ENTRY_FILE}
};

#define STRUCTURE_SIZE (sizeof(EXPECTED_STRUCTURE) / sizeof(EXPECTED_STRUCTURE[0]))

int check_or_create_entry(const char *base_dir, const SchemaEntry *entry)
{
    char full_path[PATH_MAX_LEN];
    snprintf(full_path, sizeof(full_path), "%s/%s", base_dir, entry->rel_path);

    struct stat st;
    if (stat(full_path, &st) == 0) return 0;

    if (entry->type == ENTRY_DIR){
        if (mkdir(full_path, 0755) == -1){
            perror("Erreur mkdir");
            return -1;
        }
        printf("Dossier: %s ...crée!\n", full_path);
    }else
    {
        FILE *f = fopen(full_path, "a");
        if (!f)
        {
            perror("Erreur fopen");
            return -1;
        }
        fclose(f);
        printf("Fichier: %s ...crée!\n", full_path);
    }
    return 1;
}

int init_packx(void)
{
    const char *home = getenv("HOME");
    if (!home) return -1;

    char base_dir[PATH_MAX_LEN];
    snprintf(base_dir, sizeof(base_dir), "%s/.packx", home);

    for (size_t i = 0; i < STRUCTURE_SIZE; i++)
    {
        if (check_or_create_entry(base_dir, &EXPECTED_STRUCTURE[i]) < 0)
        {
            fprintf(stderr, "Échec d'initialisation sur : %s\n", EXPECTED_STRUCTURE[i].rel_path);
            return -1;
        }
        
    }
    return 0;
}