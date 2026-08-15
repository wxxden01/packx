#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "packages.h"
#include "path_builder.h"

#define PATH_MAX_LEN 256

int parse_line(const char *line, package_t *pkg)
{
    if (!line || !pkg) return 1;

    // %63[^|] lit au maximum 63 caractères tant que ce n'est pas un '|'
    // %32[^\n] lit la taille sans inclure le saut de ligne
    int matched = sscanf(line, "%31[^|]|%15[^|]|%63[^|]|%15[^|]|%32[^\n]", 
                         pkg->name, 
                         pkg->version, 
                         pkg->full_name,
                         pkg->size,
                         pkg->hash);
    
    return (matched == 5) ? 0 : 1;
}

int db_pkg_reader(int source_db, const char *target_pkg)
{
    const char *db_file = NULL;

    if (source_db == 1)
    {
        db_file = "installed.db";
    } 
    else 
    {
        db_file = "cache/repo.db";
    }
    
    // static const char *db_file = "installed.db"; 
    // static const char *db_mirror_file = "repo.db";
    
    char *full_path = make_path(db_file);
    if (!full_path)
    {
        return -1;
    }
    
    FILE *file = fopen(full_path, "r");
    if (!file) {
        perror("Erreur lors de l'ouverture de la base de données");
        return -1;
    }

    char line[256];
    package_t pkg;
    int found = 0;

    while (fgets(line, sizeof(line), file)) {
        if (parse_line(line, &pkg) == 0) {
            // Si le nom du paquet correspond à celui recherché
            if (strcmp(pkg.name, target_pkg) == 0) {
                printf("Version de %s : %s\n", pkg.name, pkg.version);
                found = 1;
                break;
            }
        }
    }

    fclose(file);
    return found ? 0 : 1;
}