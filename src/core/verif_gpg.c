#include <gpgme.h>


// Fonction pour afficher les erreurs GPGME
void print_gpgme_error(gpgme_error_t err, const char *context) 
{
    fprintf(stderr, "Erreur GPGME dans '%s': %s (%s)\n", 
            context, gpgme_strsource(err), gpgme_strerror(err));
}

int verify_signature(const char *data_path, const char *sig_path, const char *keyring_path)
{
    gpgme_ctx_t ctx;
    gpg_error_t err;
    gpgme_data_t data = NULL, sig = NULL;
    gpgme_verify_result_t result;
    int ret = -1;

    // GPGME INIT
    gpgme_check_version(NULL);
    // gpgme_set_locale(NULL, LC_CTYPE, setlocal(LC_CTYPE, NULL));

    // Contexte GPGME
    err = gpgme_new(&ctx);
    if (err)
    {
        print_gpgme_error(err, "gpgme_new");
        return -1;
    }

    // Keyring
    err = gpgme_ctx_set_engine_info(ctx, GPGME_PROTOCOL_OpenPGP, NULL, keyring_path);
    if (err)
    {
        print_gpgme_error(err, "gpgme_ctx_set_engine_info");
        goto cleanup;
    }

    // Ouverture du fichier de données
    err = gpgme_data_new_from_file(&data, data_path, 1);
    if (err) {
        print_gpgme_error(err, "gpgme_data_new_from_file (sig)");
        goto cleanup;
    }

    
    // Ouvrir le fichier de signature (repo.db.sig)
    err = gpgme_data_new_from_file(&sig, sig_path, 1);
    if (err) {
        print_gpgme_error(err, "gpgme_data_new_from_file (sig)");
        goto cleanup;
    }

    // VÉRIFICATION DE LA SIGNATURE (le moment de vérité !)
    err = gpgme_op_verify(ctx, sig, data, NULL);
    if (err) {
        print_gpgme_error(err, "gpgme_op_verify");
        goto cleanup;
    }

    // Analyser le résultat
    result = gpgme_op_verify_result(ctx);
    if (!result) {
        fprintf(stderr, "Erreur: Aucun résultat de vérification\n");
        goto cleanup;
    }

    // Parcourir toutes les signatures trouvées
    gpgme_signature_t sig_result = result->signatures;
    while (sig_result) {
        if (sig_result->status == !GPG_ERR_NO_ERROR) {
            fprintf(stderr, "Signature invalide !\n");
            // printf("Fingerprint: %s\n", sig_result->fpr);
            // printf("Timestamp: %ld\n", sig_result->timestamp);
            ret = -1;
        }
        ret = 0;
        sig_result = sig_result->next;
    }

    // Si aucune signature n'a été trouvée
    if (!result->signatures) {
        fprintf(stderr, "Aucune signature trouvée dans le fichier\n");
        ret = -1;
    }

cleanup:
    if (data) gpgme_data_release(data);
    if (sig) gpgme_data_release(sig);
    if (ctx) gpgme_release(ctx);
    
    return ret;
}