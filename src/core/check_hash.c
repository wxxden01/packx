#include <stdio.h>
#include <openssl/sha.h>

#include "packages.h"
#include "path_builder.h"

#define PATH_MAX_LEN 256
package_t pkg_data;

// Pour SHA256
int check_SHA256(char *pkg_name)
{
    if (pkg_finder(2, pkg_name, &pkg_data) == -1)
    {
        printf("Le paquet %s est déjà installé sur cette machine!\n", pkg_name);
        return -1;
    }

    char *hash = pkg_data.hash;
    char *new_hash = make_hash_SHA256(pkg_name, &hash);
    if (new_hash != 0)
    {
        printf("Problème lors du hachage!\n");
        return -1;
    }

    printf("ok pour le moment\n");
    
    return 0;
}

int make_hash_SHA256(char *pkg_name, char *hash)
{
    static char file_path[PATH_MAX_LEN];
    const char location[6] = "cache";
    snprintf(file_path, sizeof(file_path), "%s/%s", location, pkg_name);

    FILE *file = fopen(pkg_data.name, "rb");
    if (!file)
        return 1;

    SHA256_CTX ctx;
    SHA256_Init(&ctx);

    unsigned char buffer[8192];
    size_t n;

    while ((n = fread(buffer, 1, sizeof(buffer), file)) > 0)
        SHA256_Update(&ctx, buffer, n);

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_Final(hash, &ctx);

    fclose(file);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        printf("%02x", hash[i]);

    printf("\n");

    return 0;
}