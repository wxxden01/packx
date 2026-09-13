#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <libgen.h>
#include <archive.h>
#include <archive_entry.h>

int decompress(const char *nom_fichier) {
    // 1. Sauvegarder le dossier courant pour pouvoir y revenir après
    char cwd_orig[1024];
    if (getcwd(cwd_orig, sizeof(cwd_orig)) == NULL) {
        return -1;
    }

    // 2. Extraire le chemin du dossier parent et le nom du fichier
    char *path_copy1 = strdup(nom_fichier);
    char *path_copy2 = strdup(nom_fichier);
    
    char *dir_cible = dirname(path_copy1);
    char *fichier_nom = basename(path_copy2);

    // 3. Se déplacer dans le dossier où se trouve l'archive
    if (chdir(dir_cible) != 0) {
        free(path_copy1);
        free(path_copy2);
        return -1;
    }

    // 4. Extraction classique avec libarchive (sur le nom du fichier seul)
    struct archive *a = archive_read_new();
    struct archive *ext = archive_write_disk_new();
    struct archive_entry *entry;
    int r;
    int succes = 0;

    archive_read_support_filter_gzip(a);
    archive_read_support_format_tar(a);
    archive_write_disk_set_options(ext, ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM);

    if (archive_read_open_filename(a, fichier_nom, 10240) == ARCHIVE_OK) {
        while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
            r = archive_write_header(ext, entry);
            if (r == ARCHIVE_OK) {
                const void *buff;
                size_t size;
                int64_t offset;

                while (archive_read_data_block(a, &buff, &size, &offset) == ARCHIVE_OK) {
                    archive_write_data_block(ext, buff, size, offset);
                }
            }
            archive_write_finish_entry(ext);
        }
        succes = 1;
    }

    archive_read_close(a);
    archive_read_free(a);
    archive_write_close(ext);
    archive_write_free(ext);

    free(path_copy1);
    free(path_copy2);

    // 5. Revenir au dossier d'origine
    chdir(cwd_orig);

    return succes ? 0 : -1;
}