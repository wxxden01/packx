#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <curl/curl.h>

#include "path.h"
#include "mirror.h"
#include "path_builder.h"
#include "packages.h"
#include "verif_gpg.h"
#include "packx_color.h"

#define PATH_MAX_LEN 256

// Vérifie qu'au moins un mirroir est définit
int check_mirror_list()
{
    static const char *mirror_file = "mirror.txt"; 
    char *full_path = generate_path(PACKX_CONFIG_DIR, mirror_file);

    FILE *file = fopen(full_path, "r");
    if (!file)
    {
        perror("Erreur lors de l'ouverture de la base de données");
        return -1;
    }

    // On vérifie que le fichier ne soit pas vide
    int ch = fgetc(file);
    if (ch == EOF) {
        fclose(file);
        return -1; 
    }

    fclose(file);
    return 0;
}

// choisir le mirroir à partir de la liste des mirroirs définit
char *select_mirror()
{
    static const char *mirror_file = "mirror.txt"; 
    char *full_path = generate_path(PACKX_CONFIG_DIR, mirror_file);

    FILE *file = fopen(full_path, "r");
    if (!file) {
        perror("Erreur lors de l'ouverture de la base de données");
        return NULL;
    }

    char line[256];
    char *found_line = NULL;

    while (fgets(line, sizeof(line), file)) {
        size_t len = strlen(line);
        // Enlève le retour à la ligne
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
        found_line = strdup(line);
        break;
    }

    fclose(file);
    return found_line;
}

size_t write_to_file(void *contents, size_t size, size_t nmemb, void *userp) {
    FILE *fp = (FILE *)userp;
    size_t written = fwrite(contents, size, nmemb, fp);
    return written;
}

// Vérifier que le paquet est disponible sur le mirroir
int download_from_mirror(const char *mirror, const char *file_name)
{
    CURL *curl;
    CURLcode res;
    FILE *fp;

    // Construction de chemin vers le certificats du serveur
    const char *certificate_file = "certs/nginx-selfsigned.crt";
    char *certificate_file_path = generate_path(PACKX_CONFIG_DIR, certificate_file);

    // Construction du chemin vers le repo du miroir (Distant)
    static char url_db_mirror[PATH_MAX_LEN];
    snprintf(url_db_mirror, sizeof(url_db_mirror), "%s/%s", mirror, file_name);
    printf("FROM URL: %s\n", url_db_mirror);

    // Construction du chemin vers le cache (Local)
    static char dir_name[PATH_MAX_LEN];
    snprintf(dir_name, sizeof(dir_name), "%s", file_name);
    char *output_path = generate_path(PACKX_CACHE_DIR, dir_name);
    printf("TO PATH: %s\n", output_path);

    fp = fopen(output_path, "wb");
    if (fp == NULL)
    {
        fprintf(stderr, "Impossible d'ouvrir %s en écriture\n", output_path);
        return -1;
    }
    
    curl = curl_easy_init();
    if (curl)
    {
        // Définition de l'url sur lequel on travail
        curl_easy_setopt(curl, CURLOPT_URL, url_db_mirror);

        // Récupère le certificat du serveur
        curl_easy_setopt(curl, CURLOPT_CAINFO, certificate_file_path);

        // Enregistrer le callback qui écrit dans le fichier
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_file);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

        // Suivre les redirections
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        // Exécuter le téléchargement
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            fprintf(stderr, "Echec du téléchargement: %s\n", curl_easy_strerror(res));
            fclose(fp);
            curl_easy_cleanup(curl);
            return -1;
        }
        curl_easy_cleanup(curl);
    }
    
    fclose(fp);
    return 0;
}

int mirror_check(void)
{
    if (check_mirror_list() != 0)
    {
        fprintf(stderr, "Erreur : Le fichier est vide, aucun mirroir renseigné!\nVeuillez ajouter un mirroir dans le fichier ~/.packx/mirror.txt\n");
        return -1;
    }

    // Selection un mirroir dans sa liste
    char *mirror = select_mirror();
    if (mirror == NULL)
    {
        return -1;
    }

    // Télécharge le fichier repo.db ainsi que sa signature
    if (download_from_mirror(mirror, "repo.db") != 0)
    {
        printf("erreur dw repo\n");
        return -1;
    }

    if (download_from_mirror(mirror, "repo.db.sig") != 0)
    {
        printf("erreur dw sig repo!\n");
        return -1;
    }

    // Vérifier la signature
    char *repo_path = generate_path(PACKX_CACHE_DIR, "repo.db");
    char *sig_repo_path = generate_path(PACKX_CACHE_DIR, "repo.db.sig");
    if (verify_signature(repo_path, sig_repo_path, PACKX_KEYRING_DIR) == 0) {
        printf(SUCCES"Vérification de la sigature du dépot réussie!\n"NORMAL);
        return 0;
    } else {
        printf(ERROR"Vérification de la signature du dépot échouée!\n");
        return 1;
    }

    free(mirror);

    return 0;
}