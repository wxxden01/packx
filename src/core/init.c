#include <stdio.h>
#include <sys/stat.h>

#include "init.h"
#include "path.h"

int is_dir(const char *chemin)
{
    struct stat buffer;

    if (stat(chemin, &buffer) == 0)
    {
        return S_ISDIR(buffer.st_mode);
    }
    
    return 0; // le dossier n'existe pas!
}


int init_source_dir(const char *dir)
{
    if (!is_dir(dir))
    {
        if (mkdir(dir, 0700) != 0)
        {
            perror("mkdir");
            return 1;
        }

        printf("Dossier %s créer!\n", dir);
        return 0;
    }
    return 0;
}

int init_db(const char *file)
{
    FILE *f = fopen(file, "a");

    if (!f)
    {
        perror("fopen");
        return 1;
    }
    fclose(f);
    return 0;
}

int init_packx(void)
{
    const char *source = get_packx_dir(); // chemin source : ~/.packx
    const char *db_file = get_installed_db_path(); // bdd : ~/.packx/installed.db
    
    if (init_source_dir(source) != 0)
        return 1;

    if (init_db(db_file) != 0)
        return 1;

    return 0;
}