#include <stdbool.h>
#include <string.h>

// TEMPORAIRE, a terme faire la liste des paquets installés de puis le dossier ~/.db
const char *available_packages[] = {
    "htop",
    "vim",
    "git",
    "gcc",
    NULL
};

bool package_exist(const char *name)
{
    for (size_t i = 0; available_packages[i] != NULL; i++)
    {
        if (strcmp(name, available_packages[i]) == 0){
            return true;
        }
    }
    return false;
}