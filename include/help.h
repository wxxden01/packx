#ifndef HELP_H
#define HELP_H

/**
 * @brief Affiche une aide sur l'utilisation de REX ou sur un paquet en particulier
 * @param argc Nombre d'arguments, si < 3 fournit une liste de commande utilisable pour REX
 * @param argv Récupère le nom du paquet et fournit des détailles sur ce dernier si argc vaut 3
 */
int packx_help(int argc, char **argv);

#endif