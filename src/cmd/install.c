#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>

#include "path.h"
#include "path_builder.h"
#include "mirror.h"
#include "packages.h"
#include "check_hash.h"
#include "has_sudo.h"
#include "packx_color.h"
#include "config.h"
#include "decompress.h"

#define PATH_MAX_LEN 256

package_t pkg_data;

int packx_install(char *pkg_selected)
{
    // On s'assure que la commande est bien lancé en mode super utilisateur
    if (sudo() == -1)
    {
        printf(ERROR"Cette commande doit impérativement être lancé en tant que super utilisateur ou  avec 'sudo'!"NORMAL);
        return -1;
    }
    if (pkg_selected == NULL)
    {
        printf(WARNING"Mauvaise utilisation de la commande 'install'\n"BOLD"Utilisation : sudo packx install <pkg>"NORMAL);
        return -1;
    }
    
    // Vérifie que le paquet n'est pas installé
    if (pkg_installed(pkg_selected) == 0)
    {
        printf(WARNING"Le paquet %s est déjà installé sur cette machine!\n"NORMAL, pkg_selected);
        return -1;
    }
    // Vérifie la config du mirroir
    if (mirror_check() != 0)
    {
        return -1;
    }

    // Vérifier si l'archive existe sur le mirroir
    if (pkg_finder(2, pkg_selected, &pkg_data))
    {
        printf("Le paquet %s n'est pas disponible sur ce miroir ou n'existe pas!\nVérifier l'hortograhe et réssayer!\n", pkg_selected);
        printf("%s\n", pkg_data.name);
        return -1;
    }
    printf("Paquet %s disponible sur le miroir!\n", pkg_selected);

    // Télécharger l'archive
    char *mirror = select_mirror();
    if (mirror == NULL)
    {
        return -1;
    }

    if (download_from_mirror(mirror, "packx-repo/x86_64/pkgs", pkg_data.full_name) != 0)
    {
        printf("erreur dw archive!\n");
        return -1;
    }
    // Vérifie le hash du paquet
    if (check_SHA256(pkg_data.full_name, pkg_data.hash))
    {
        return -1;
    }
    printf(SUCCES"Intégrité du paquet vérifier!\n"NORMAL);
    
    if (check_var() != 0)
    {
        printf("err /etc/profile.d/packx.sh!\n");
        return -1;
    }

    char *archive_path = generate_path(PACKX_CACHE_DIR, pkg_data.full_name);
    chmod(archive_path, 0755);
    if (decompress(archive_path) != 0)
    {
        printf("Erreur à la décompression de l'archive!\n");
    }
    
    pid_t pid = fork();
    if (pid == 0) {
        // Processus fils
        char bash_path[PATH_MAX_LEN];
        snprintf(bash_path ,PATH_MAX_LEN, "%s/%s/scripts/install.sh", PACKX_CACHE_DIR, pkg_data.name);
        execl("/bin/bash", "bash", bash_path, NULL);
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
    return 1;
}