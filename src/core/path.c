#include <stdlib.h>
#include <stdio.h>

#define PATH_MAX_LEN 256

static char PACKX_DIR[PATH_MAX_LEN];
static char db_path[PATH_MAX_LEN];

const char *get_packx_dir(void)
{
    const char *home = getenv("HOME");
    snprintf(PACKX_DIR, sizeof(PACKX_DIR), "%s/.packx", home);
    return PACKX_DIR;
}

const char *get_installed_db_path(void)
{
    snprintf(db_path, sizeof(db_path), "%s/installed.db", get_packx_dir());
    return db_path;
}   