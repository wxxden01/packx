#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "has_sudo.h"
#include "version.h"
#include "packages.h"
#include "packx_color.h"

#define PATH_MAX_LEN 256

int packx_version(char *target_pkg)
{
    (void)target_pkg;
    printf(SUCCES "PACKX version : %s\n" NORMAL, PACKX_VERSION);
    return 0;
}