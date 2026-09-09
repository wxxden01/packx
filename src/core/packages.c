#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "packages.h"
#include "path.h"
#include "path_builder.h"
#include "packx_color.h"

#define PATH_MAX_LEN 256

int parse_line(const char *line, package_t *pkg)
{
    if (!line || !pkg) return 1;

    // %63[^|] lit au maximum 63 caractères tant que ce n'est pas un '|'
    // %32[^\n] lit la taille sans inclure le saut de ligne
    int matched = sscanf(line, "%31[^|]|%15[^|]|%63[^|]|%15[^|]|%255[^\n]", 
                         pkg->name, 
                         pkg->version, 
                         pkg->full_name,
                         pkg->size,
                         pkg->hash);
    
    return (matched == 5) ? 0 : 1;
}

int pkg_finder(int source_db, const char *target_pkg, package_t *out_pkg) {
    if (!target_pkg || !out_pkg) return -1;

    char *full_path;
    if (source_db == 1)
    {
        char *db_file = "installed.db";
        full_path = generate_path(PACKX_DB_DIR, db_file);
    }else
    {
        char *db_file = "repo.db";
        full_path = generate_path(PACKX_CACHE_DIR, db_file);
    }

    FILE *file = fopen(full_path, "r");
    free(full_path); // IMPORTANT : Libérer la mémoire allouée par make_path
    
    if (!file) {
        perror(ERROR "Erreur lors de l'ouverture de la base de données" NORMAL);
        return -1;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (parse_line(line, out_pkg) == 0) {
            if (strcmp(out_pkg->name, target_pkg)) {
                fclose(file);
                return 0;
            }
        }
    }

    fclose(file);
    return -1; // Non trouvé
}