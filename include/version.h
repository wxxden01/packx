#ifndef VERSION_H
#define VERSION_H

#define NAME "Packx"
#define PACKX_V "1.0.0\n"
#define PACKX_VERSION NAME"-"PACKX_V

/**
 * @brief renvoie la version d'un paquet ou de Packx si aucun paquet n'est spécifié
 * @param argc Nombre d'arguments
 * @param argv Argument précis
 * @return version du paquet ou de Packx
 */
int packx_version(int argc, char **argv);

#endif