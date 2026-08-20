#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <curl/curl.h>

#include "mirror.h"
#include "path_builder.h"
#include "packages.h"

#define PATH_MAX_LEN 256

// Vérifie qu'au moins un mirroir est définit
int check_mirror_list(char *full_path)
{
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
char *select_mirror(const char *file_name)
{
    FILE *file = fopen(file_name, "r");
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
    const char *certificate_file = "certificates/nginx-selfsigned.crt";
    char *certificate_file_path = make_path(certificate_file);
    if (!certificate_file_path)
    {
        printf("Erreur lors du chargement du certificat!\nVérifier que vous avez bien installez le certificat du miroir dans ~/.packx/certificates\n");
        return -1;
    }

    // Construction du chemin vers le repo du miroir (Distant)
    static char url_db_mirror[PATH_MAX_LEN];
    snprintf(url_db_mirror, sizeof(url_db_mirror), "%s/%s", mirror, file_name);
    printf("FROM URL: %s\n", url_db_mirror);

    // Construction du chemin vers le cache (Local)
    static char dir_name[PATH_MAX_LEN];
    snprintf(dir_name, sizeof(dir_name), "cache/%s", file_name);
    char *output_path = make_path(dir_name);
    if (!output_path)
    {
        return -1;
    }
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
    static const char *mirror_file = "mirror.txt"; 
    
    char *full_path = make_path(mirror_file);
    if (!full_path)
    {
        return -1;
    }

    if (check_mirror_list(full_path) != 0)
    {
        fprintf(stderr, "Erreur : Le fichier est vide, aucun mirroir renseigné!\nVeuillez ajouter un mirroir dans le fichier ~/.packx/mirror.txt\n");
        return -1;
    }

    char *mirror = select_mirror(full_path);
    if (mirror == NULL)
    {
        return -1;
    }

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
    
    free(mirror);
    free(full_path);

    return 0;
}