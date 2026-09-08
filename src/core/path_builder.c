#include <stdio.h>
#include <stdlib.h>

#include "path.h"
#include "paths.h"

#define PATH_MAX_LEN 256

char *generate_path(const char *path, const char *file_name)
{
    size_t len = snprintf(NULL, 0, "%s/%s", path, file_name) + 1;
    char *generated_path = malloc(len);
    if (generated_path == NULL) {
        return NULL;
    }
    snprintf(generated_path, len, "%s/%s", path, file_name);
    return generated_path;
}