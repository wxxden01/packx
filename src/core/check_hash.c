#include <stdio.h>
#include <openssl/evp.h>
#include <string.h>

#include "check_hash.h"
#include "packages.h"
#include "path_builder.h"

#define PATH_MAX_LEN 256

// Génère le hash en SHA256 d'un paquet donné
int hash_generator_SHA256(char *pkg_name, char *output_hash)
{
    static char file_path[PATH_MAX_LEN];
    const char location[6] = "cache";
    snprintf(file_path, sizeof(file_path), "%s/%s", location, pkg_name);
    char *output_path = make_path(file_path);
    if (!output_path)
    {
        return -1;
    }

    FILE *file = fopen(output_path, "rb");
    if (!file)
    {
        printf("Problème à l'ouverture du fichier!\n");
        return 1;
    }

    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    if (!mdctx)
    {
        fclose(file);
        return 1;
    }

    if (EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL) != 1)
    {
        EVP_MD_CTX_free(mdctx);
        fclose(file);
        return 1;
    }

    unsigned char buffer[8192];
    size_t n;

    while ((n = fread(buffer, 1, sizeof(buffer), file)) > 0)
    {
        if (EVP_DigestUpdate(mdctx, buffer, n) != 1)
        {
            EVP_MD_CTX_free(mdctx);
            fclose(file);
            return 1;
        }
    }

    unsigned char raw_digest[EVP_MAX_MD_SIZE];
    unsigned int digest_len = 0;

    if (EVP_DigestFinal_ex(mdctx, raw_digest, &digest_len) != 1)
    {
        EVP_MD_CTX_free(mdctx);
        fclose(file);
        return 1;
    }

    EVP_MD_CTX_free(mdctx);
    fclose(file);

    // Convert raw binary digest to hex string in output_hash
    if (output_hash != NULL)
    {
        for (unsigned int i = 0; i < digest_len; i++)
            sprintf(output_hash + (i * 2), "%02x", raw_digest[i]);

        output_hash[digest_len * 2] = '\0';
    }
    return 0;
}

int check_SHA256(char *pkg_name)
{
    // Récupération des info de paquet sur la bdd du mirroir
    package_t pkg_data;
    pkg_finder(2, pkg_name, &pkg_data);

    // Génération de hash du paquet téléchargé 
    char hash_generate[257];
    if (hash_generator_SHA256(pkg_data.full_name, hash_generate))
    {
        printf("Problème lors du hachage!\n");
        return -1;
    }

    // Vérification avec le hash de référence
    if (strcmp(pkg_data.hash, hash_generate) != 0)
    {
        // supprimer l'archive
        printf("Les hash ne sont pas identique, par soucis d'intégrité nous ne pouvons pas installer le paquet demander!\n");
        return -1;
    }
    
    return 0;
}