<div align="center">

# PACKX

Gestionnaire de paquets léger pour distributions Linux en construction.

![Eco](https://img.shields.io/badge/Langage-C-blue?style=for-the-badge)
![Linux](https://img.shields.io/badge/OS-Linux-yellow?style=for-the-badge&logo=linux)
[![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)](LICENSE)
[![Version](https://img.shields.io/badge/version-0.1.0-blue?style=for-the-badge)]()

## À propos

PACKX est un gestionnaire de paquets minimaliste conçu pour les distributions Linux en phase de développement (stade BLFS - Beyond Linux From Scratch). Il n'a pas pour vocation de concurrencer `apt`, `pacman`, `dnf` ou autres gestionnaires matures, mais offre une alternative simple et facile à intégrer pour les petites distributions en construction.
</div>

### Philosophie

- **Simplicité** : Code C propre et compréhensible
- **Légèreté** : Dépendances minimales
- **Transparence** : Format de base de données lisible
- **Sécurité** : Vérification GPG + MD5

## Fonctionnalités

- Installation/suppression de paquets (d'autres fonctionnalités arrivent!)
- Vérification cryptographique
- Résolution de dépendances
- Mise à jour de paquets
- Cache local
- Base de données locale persistante

## Prérequis

- GCC ou Clang
- Make
- libcurl (pour les téléchargements)
- libgpgme (pour la vérification GPG)
___

# Cloner le dépôt
``` bash
git clone https://github.com/wxxden01/packx.git
cd packx

# Compiler
make

# L'exécutable se trouve dans build/
./build/packx -h
```

# Etat
- [ROADMAP](/ROADMAP.md)
- Non fonctionnel à ce stade