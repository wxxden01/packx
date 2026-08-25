#ifndef VERIF_GPG_H
#define VERIF_GPG_H

#include <gpgme.h>

void print_gpgme_error(gpgme_error_t err, const char *context);

int verify_signature(const char *data_path, const char *sig_path, const char *keyring_path);

#endif
