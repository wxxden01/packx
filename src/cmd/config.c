#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "mirror.h"
#include "path_builder.h"

char *check_linux_distro()
{
    FILE *file = fopen("/etc/os-release", "r");
    if (!file) {
        printf("Impossible d'ouvrir /etc/os-release\n");
        return NULL;
    }

    char line[256];
    char *result = NULL;
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "NAME=", 5) == 0) {
            char *val = line + 5;
            // Retirer le \n
            size_t len = strlen(val);
            if (len > 0 && val[len-1] == '\n') val[len-1] = '\0';
            // Retirer les guillemets
            if (val[0] == '"') {
                val++;
                len = strlen(val);
                if (len > 0 && val[len-1] == '"') val[len-1] = '\0';
            }
            result = strdup(val);
            break;
        }
    }
    fclose(file);
    return result;
}   

int check_var(void)
{
    // char *distro = check_linux_distro();
    
    char *path = "/etc/profile.d";
    char *file_name = "packx-var.sh";
    char *full_path = generate_path(path, file_name);

    FILE *file = fopen(full_path, "r");
    if (!file)
    {
        FILE *new_file = fopen(full_path, "w");
        if (!new_file) 
        {
            return -1;
        }
        chmod(full_path, 0755);
        fprintf(new_file, "export PACKX_SOURCE='/usr/bin'");
        fclose(new_file);
    }else{
        fclose(file);
        return 0;
    }

    return 0;
}

int show_config(int argc, char **argv) 
{
    (void)argc;
    (void)argv;
    // afficher le miroir par défault
    char *default_mirror = select_mirror();
    if (default_mirror == NULL)
    {
        return -1;
    }

    printf("Config actuelle de Packx:\n");
    printf("Miroir par défault : %s\n", default_mirror);
    return 0;
}