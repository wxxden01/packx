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
    // %15[^\n] lit la taille sans inclure le saut de ligne
    int matched = sscanf(line, "%63[^|]|%15[^|]|%15[^\n]", 
                         pkg->name, 
                         pkg->version, 
                         pkg->size);
    
    return (matched == 3) ? 0 : 1;
}

int db_pkg_reader(const char *target_pkg)
{
    static const char *db_file = "installed.db"; 
    
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