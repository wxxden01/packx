#ifndef PACKAGES_H
#define PACKAGES_H
#include <stdbool.h>

/**
 * @brief Renvoie un booléen si le paquet spécifier est trouvé
 * @param name
 * @result true si le paquet est trouvé, sinon false
 */
bool package_exist(const char *name);

#endif 