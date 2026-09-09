#ifndef HAS_SUDO_H
#define HAS_SUDO_H

/**
 * @brief Définit si l'utilisateur à utilisé 'sudo' pour lancer la commande
 * @param first_arg Première argument de la commande
 * @return 0 si 'sudo' utilisé et -1 en cas contraire
 */
int sudo(char *first_arg);

#endif