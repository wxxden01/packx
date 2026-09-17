#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "has_sudo.h"
#include "packx_color.h"

#define BUFFER 256

int packx_remove(char *target_pkg)
{
    char full_path[BUFFER];
    char *path = "/var/lib/packx/pkgs";
    snprintf(full_path ,BUFFER, "%s/%s/scripts/remove.sh", path, target_pkg);

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