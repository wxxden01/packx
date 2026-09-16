#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "has_sudo.h"
#include "packx_color.h"

#define BUFFER 256

int packx_remove(int argc, char **argv)
{
    (void)argc;
    char pkg_selected[32];
    if (sudo(argv[0]))
    {
        printf("ok!\n");
        return 0;
    }else
    {
        printf(WARNING "Mauvaise utilisation de la commande! 'sudo packx remove <pkg>'\n" NORMAL);
        return -1;
    }

    char full_path[BUFFER];
    char *path = "/var/lib/packx/pkgs";
    snprintf(full_path ,BUFFER, "%s/%s/scripts/remove.sh", path, pkg_selected);

    pid_t pid = fork();
    if (pid == 0) {
        // Processus fils
        perror("execl"); // S'exécute seulement si execl échoue
        return -1;
    } else if (pid > 0) {
        // Processus père
        int status;
        wait(&status); // Attend la fin du fils
        printf("Script terminé avec le statut %d\n", WEXITSTATUS(status));
    } else {
        perror("fork");
    }
    printf("%s\n", full_path);
    
    return 0;
}