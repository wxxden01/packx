#ifndef CHECK_HASH_H
#define CHECK_HASH_H

int check_SHA256(char *pkg_name);

int make_hash_SHA256(char *pkg_name, char *hash);
#endif